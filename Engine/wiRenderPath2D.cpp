#include "wiRenderPath2D.h"
#include "wiResourceManager.h"
#include "wiSprite.h"
#include "wiSpriteFont.h"
#include "wiRenderer.h"

using namespace wi::graphics;

namespace wi
{
	void RenderPath2D::DeleteGPUResources()
	{
		current_buffersize = {};
		current_layoutscale = 0; // invalidate layout

		rtFinal = {};
		rtFinal_MSAA = {};
		rtStencilExtracted = {};
		stencilScaled = {};
	}

	void RenderPath2D::ResizeBuffers()
	{
		current_buffersize = GetInternalResolution();
		current_layoutscale = 0; // invalidate layout

		GraphicsDevice* device = wi::graphics::GetDevice();

		const uint32_t sampleCount = std::max(getMSAASampleCount(), getMSAASampleCount2D());

		const Texture* dsv = GetDepthStencil();
		if (dsv != nullptr && (resolutionScale != 1.0f || dsv->GetDesc().sample_count != sampleCount))
		{
			TextureDesc desc = GetDepthStencil()->GetDesc();
			desc.layout = ResourceState::SHADER_RESOURCE;
			desc.bind_flags = BindFlag::RENDER_TARGET | BindFlag::SHADER_RESOURCE;
			desc.format = Format::R8_UINT;
			desc.layout = ResourceState::SHADER_RESOURCE;
			device->CreateTexture(&desc, nullptr, &rtStencilExtracted);
			device->SetName(&rtStencilExtracted, "rtStencilExtracted");

			desc.width = GetPhysicalWidth();
			desc.height = GetPhysicalHeight();
			desc.sample_count = sampleCount;
			desc.bind_flags = BindFlag::DEPTH_STENCIL;
			desc.format = Format::D24_UNORM_S8_UINT;
			desc.layout = ResourceState::DEPTHSTENCIL;
			device->CreateTexture(&desc, nullptr, &stencilScaled);
			device->SetName(&stencilScaled, "stencilScaled");
		}
		else
		{
			rtStencilExtracted = {};
			stencilScaled = {};
		}

		{
			TextureDesc desc;
			desc.bind_flags = BindFlag::RENDER_TARGET | BindFlag::SHADER_RESOURCE;
			desc.format = Format::R8G8B8A8_UNORM;
			desc.width = GetPhysicalWidth();
			desc.height = GetPhysicalHeight();
			device->CreateTexture(&desc, nullptr, &rtFinal);
			device->SetName(&rtFinal, "rtFinal");

			if (sampleCount > 1)
			{
				desc.sample_count = sampleCount;
				desc.bind_flags = BindFlag::RENDER_TARGET;
				desc.misc_flags = ResourceMiscFlag::TRANSIENT_ATTACHMENT;
				desc.layout = ResourceState::RENDERTARGET;
				device->CreateTexture(&desc, nullptr, &rtFinal_MSAA);
				device->SetName(&rtFinal_MSAA, "rtFinal_MSAA");
			}
		}
	}
	void RenderPath2D::ResizeLayout()
	{
		current_layoutscale = GetDPIScaling();
	}

	void RenderPath2D::Update(float dt)
	{
		if (current_layoutscale != GetDPIScaling())
		{
			ResizeLayout();
		}

		GetGUI().Update(*this, dt);

		for (auto& x : layers)
		{
			for (auto& y : x.items)
			{
				switch (y.type)
				{
				default:
				case RenderItem2D::TYPE::SPRITE:
					if (y.sprite != nullptr)
					{
						y.sprite->Update(dt);
					}
					break;
				case RenderItem2D::TYPE::FONT:
					if (y.font != nullptr)
					{
						y.font->Update(dt);
					}
					break;
				}
			}
		}

		RenderPath::Update(dt);
	}
	void RenderPath2D::FixedUpdate()
	{
		for (auto& x : layers)
		{
			for (auto& y : x.items)
			{
				switch (y.type)
				{
				default:
				case RenderItem2D::TYPE::SPRITE:
					if (y.sprite != nullptr)
					{
						y.sprite->FixedUpdate();
					}
					break;
				case RenderItem2D::TYPE::FONT:
					if (y.font != nullptr)
					{
						y.font->FixedUpdate();
					}
					break;
				}
			}
		}

		RenderPath::FixedUpdate();
	}
	void RenderPath2D::PreRender()
	{
		XMUINT2 internalResolution = GetInternalResolution();

		if (current_buffersize.x != internalResolution.x || current_buffersize.y != internalResolution.y)
		{
			ResizeBuffers();
		}

		RenderPath::PreRender();
	}
	void RenderPath2D::Render() const
	{
		if (!rtFinal.IsValid())
		{
			// Since 0.71.694: PreRender must be called before Render() because it sets up rendering resources!
			//	The proper fix is to call PreRender() yourself for a manually managed RenderPath3D
			//	But if you don't do that, as a last resort it will be called here using const_cast
			assert(0);
			const_cast<RenderPath2D*>(this)->PreRender();
		}

		GraphicsDevice* device = wi::graphics::GetDevice();
		CommandList cmd = device->BeginCommandList();
		device->EventBegin("RenderPath2D::Render", cmd);
		wi::image::SetCanvas(*this);
		wi::font::SetCanvas(*this);

		wi::renderer::ProcessDeferredTextureRequests(cmd);

		if (GetGUIBlurredBackground() != nullptr)
		{
			wi::image::SetBackground(*GetGUIBlurredBackground());
		}

		const Texture* dsv = GetDepthStencil();

		if (rtStencilExtracted.IsValid())
		{
			wi::renderer::ExtractStencil(*dsv, rtStencilExtracted, cmd);
		}

		RenderPassImage rp[4];
		uint32_t rp_count = 0;
		if (rtFinal_MSAA.IsValid())
		{
			// MSAA:
			rp[rp_count++] = RenderPassImage::RenderTarget(
				&rtFinal_MSAA,
				RenderPassImage::LoadOp::CLEAR,
				RenderPassImage::StoreOp::DONTCARE,
				ResourceState::RENDERTARGET,
				ResourceState::RENDERTARGET
			);
			rp[rp_count++] = RenderPassImage::Resolve(&rtFinal);
		}
		else
		{
			// Single sample:
			rp[rp_count++] = RenderPassImage::RenderTarget(&rtFinal, RenderPassImage::LoadOp::CLEAR);
		}
		if (stencilScaled.IsValid())
		{
			// Scaled stencil:
			rp[rp_count++] = RenderPassImage::DepthStencil(&stencilScaled, RenderPassImage::LoadOp::CLEAR, RenderPassImage::StoreOp::DONTCARE);
		}
		else if (dsv != nullptr)
		{
			// Native stencil:
			rp[rp_count++] = RenderPassImage::DepthStencil(dsv, RenderPassImage::LoadOp::LOAD, RenderPassImage::StoreOp::STORE);
		}
		device->RenderPassBegin(rp, rp_count, cmd);

		Viewport vp;
		vp.width = (float)rtFinal.GetDesc().width;
		vp.height = (float)rtFinal.GetDesc().height;
		device->BindViewports(1, &vp, cmd);

		Rect rect;
		rect.left = 0;
		rect.right = (int32_t)rtFinal.GetDesc().width;
		rect.top = 0;
		rect.bottom = (int32_t)rtFinal.GetDesc().height;
		device->BindScissorRects(1, &rect, cmd);

		if (stencilScaled.IsValid())
		{
			wi::renderer::ScaleStencilMask(vp, rtStencilExtracted, cmd);
		}

		device->EventBegin("Layers", cmd);
		for (auto& x : layers)
		{
			for (auto& y : x.items)
			{
				switch (y.type)
				{
				default:
				case RenderItem2D::TYPE::SPRITE:
					if (y.sprite != nullptr)
					{
						y.sprite->Draw(cmd);
					}
					break;
				case RenderItem2D::TYPE::FONT:
					if (y.font != nullptr)
					{
						y.font->Draw(cmd);
					}
					break;
				}
			}
		}
		device->EventEnd(cmd);

		GetGUI().Render(*this, cmd);

		device->RenderPassEnd(cmd);

		device->EventEnd(cmd);

		RenderPath::Render();
	}
	void RenderPath2D::Compose(CommandList cmd) const
	{
		GraphicsDevice* device = wi::graphics::GetDevice();
		device->EventBegin("RenderPath2D::Compose", cmd);

		wi::image::Params fx;
		fx.enableFullScreen();
		fx.blendFlag = wi::enums::BLENDMODE_PREMULTIPLIED;
		if (colorspace != ColorSpace::SRGB)
		{
			// Convert the regular SRGB result of the render path to linear space for HDR compositing:
			fx.enableLinearOutputMapping(hdr_scaling);
		}
		wi::image::Draw(&GetRenderResult(), fx, cmd);

		device->EventEnd(cmd);

		RenderPath::Compose(cmd);
	}


	void RenderPath2D::AddSprite(wi::Sprite* sprite, const std::string& layer, const int order)
	{
		for (auto& x : layers)
		{
			if (!x.name.compare(layer))
			{
				x.items.push_back(RenderItem2D());
				x.items.back().type   = RenderItem2D::TYPE::SPRITE;
				x.items.back().sprite = sprite;
				x.items.back().order  = order;

				for (size_t j = x.items.size() - 1; j > 0; --j) {
					if (x.items[j - 1].order <= x.items[j].order)
						break;
					std::swap(x.items[j - 1], x.items[j]);
				}

				return;
			}
		}
	}
	void RenderPath2D::RemoveSprite(wi::Sprite* sprite)
	{
		for (auto& x : layers)
		{
			for (auto it = x.items.begin(); it != x.items.end(); ++it)
			{
				if ((*it).type != RenderItem2D::TYPE::SPRITE)
					continue;
				if ((*it).sprite != sprite)
					continue;
				x.items.erase(it);
				return;
			}
		}
	}
	void RenderPath2D::ClearSprites()
	{
		for (auto& x : layers)
		{
			for (auto& y : x.items)
			{
				if (y.type == RenderItem2D::TYPE::SPRITE)
				{
					y.sprite = nullptr;
				}
			}
		}
		CleanLayers();
	}
	int RenderPath2D::GetSpriteOrder(wi::Sprite* sprite)
	{
		for (auto& x : layers)
		{
			for (auto& y : x.items)
			{
				if (y.sprite == sprite)
				{
					return y.order;
				}
			}
		}
		return 0;
	}

	void RenderPath2D::AddFont(wi::SpriteFont* font, const std::string& layer, const int order)
	{
		for (auto& x : layers)
		{
			if (!x.name.compare(layer))
			{
				x.items.push_back(RenderItem2D());
				x.items.back().type  = RenderItem2D::TYPE::FONT;
				x.items.back().font  = font;
				x.items.back().order = order;

				for (size_t j = x.items.size() - 1; j > 0; --j) {
					if (x.items[j - 1].order <= x.items[j].order)
						break;
					std::swap(x.items[j - 1], x.items[j]);
				}

				break;
			}
		}
	}
	void RenderPath2D::RemoveFont(wi::SpriteFont* font)
	{
		for (auto& x : layers)
		{
			for (auto it = x.items.begin(); it != x.items.end(); ++it)
			{
				if ((*it).type != RenderItem2D::TYPE::FONT)
					continue;
				if ((*it).font != font)
					continue;
				x.items.erase(it);
				return;
			}
		}
	}
	void RenderPath2D::ClearFonts()
	{
		for (auto& x : layers)
		{
			for (auto& y : x.items)
			{
				if (y.type == RenderItem2D::TYPE::FONT)
				{
					y.font = nullptr;
				}
			}
		}
		CleanLayers();
	}
	int RenderPath2D::GetFontOrder(wi::SpriteFont* font)
	{
		for (auto& x : layers)
		{
			for (auto& y : x.items)
			{
				if (y.font == font)
				{
					return y.order;
				}
			}
		}
		return 0;
	}


	void RenderPath2D::AddLayer(const std::string& name, int order)
	{
		for (auto& x : layers)
		{
			if (!x.name.compare(name))
			{
				SetLayerOrder(name, order);
				return;
			}
		}
		RenderLayer2D layer;
		layer.name = name;
		layer.order = (int)layers.size();
		layers.push_back(layer);
		layers.back().items.clear();

		const size_t LAYER_SIZE = layers.size();
		if (order == 0)
		{
			if (LAYER_SIZE <= 1)
				layers.back().order = (int)LAYER_SIZE;
			else
				layers.back().order = layers[LAYER_SIZE - 1].order + 1;
		}
		else
		{
			layers.back().order = order;
			for (size_t i = LAYER_SIZE - 1; i > 0; --i) {
				if (layers[i - 1].order <= layers[i].order)
					break;
				std::swap(layers[i - 1], layers[i]);
			}
		}
	}
	void RenderPath2D::SetLayerOrder(const std::string& name, int order)
	{
		const size_t LAYER_SIZE = layers.size();
		for (size_t i = 0; i < LAYER_SIZE; ++i)
		{
			if (layers[i].name.compare(name) == 0)
			{
				layers[i].order = order;

				std::swap(layers[i], layers[LAYER_SIZE - 1]);
				for (size_t j = LAYER_SIZE - 1; j > 0; --j) {
					if (layers[j - 1].order <= layers[j].order)
						break;
					std::swap(layers[j - 1], layers[j]);
				}

				return;
			}
		}
	}
	void RenderPath2D::SetSpriteOrder(wi::Sprite* sprite, int order)
	{
		for (auto& layer : layers)
		{
			const size_t ITEM_SIZE = layer.items.size();
			for (size_t i = 0; i < ITEM_SIZE; ++i)
			{
				if (layer.items[i].type != RenderItem2D::TYPE::SPRITE)
					continue;
				if (layer.items[i].sprite != sprite)
					continue;

				layer.items[i].order = order;
				for (size_t j = i; j > 0; --j) {
					if (layer.items[j - 1].order <= layer.items[j].order)
						break;
					std::swap(layer.items[j - 1], layer.items[j]);
					i = j - 1;
				}
				for (size_t j = i; j < ITEM_SIZE - 1; ++j) {
					if (layer.items[j].order <= layer.items[j + 1].order)
						break;
					std::swap(layer.items[j], layer.items[j + 1]);
				}
				return;
			}
		}
	}
	void RenderPath2D::SetFontOrder(wi::SpriteFont* font, int order)
	{
		for (auto& layer : layers)
		{
			const size_t ITEM_SIZE = layer.items.size();
			for (size_t i = 0; i < ITEM_SIZE; ++i)
			{
				if (layer.items[i].type != RenderItem2D::TYPE::FONT)
					continue;
				if (layer.items[i].font != font)
					continue;

				layer.items[i].order = order;
				for (size_t j = i; j > 0; --j) {
					if (layer.items[j - 1].order <= layer.items[j].order)
						break;
					std::swap(layer.items[j - 1], layer.items[j]);
					i = j - 1;
				}
				for (size_t j = i; j < ITEM_SIZE - 1; ++j) {
					if (layer.items[j].order <= layer.items[j + 1].order)
						break;
					std::swap(layer.items[j], layer.items[j + 1]);
				}
				return;
			}
		}
	}
	void RenderPath2D::SortLayers()
	{
		if (layers.empty())
		{
			return;
		}

		std::sort(
			layers.begin(), layers.end(),
			[](RenderLayer2D& a, RenderLayer2D& b)
			{ return a.order < b.order; }
		);

		for (auto& layer : layers)
		{
			if (layer.items.empty())
			{
				continue;
			}
			std::sort(
				layer.items.begin(), layer.items.end(),
				[](RenderItem2D& a, RenderItem2D& b)
				{ return a.order < b.order; }
			);
		}
	}

	void RenderPath2D::CleanLayers()
	{
		for (auto& x : layers)
		{
			if (x.items.empty())
			{
				continue;
			}
			wi::vector<RenderItem2D> itemsToRetain(0);
			for (auto& y : x.items)
			{
				if (y.sprite != nullptr || y.font != nullptr)
				{
					itemsToRetain.push_back(y);
				}
			}
			x.items.clear();
			x.items = itemsToRetain;
		}
	}

	void RenderPath2D::RemoveRenderObjects(const std::string& layer_name, const int order)
	{
		for (auto& layer : layers)
		{
			if (layer.name.compare(layer_name) == 0)
			{
				const size_t ORDER_SIZE = std::count_if(
					layer.items.begin(), layer.items.end(),
					[&](RenderItem2D& item) { return item.order == order; }
				);
				if (ORDER_SIZE == 0)
					return;

				const size_t ITEM_SIZE = layer.items.size();
				wi::vector<RenderItem2D> itemsToRetain;
				itemsToRetain.reserve(ITEM_SIZE - ORDER_SIZE);
				for (auto& item : layer.items)
				{
					if (item.order != order)
						itemsToRetain.push_back(item);
				}
				layer.items = std::move(itemsToRetain);

				return;
			}
		}
	}
	void RenderPath2D::ChangeRenderOrder(const std::string& layer_name, const int old_order, const int new_order)
	{
		for (auto& layer : layers)
		{
			if (layer.name.compare(layer_name) == 0)
			{
				for (auto& item : layer.items)
				{
					if (item.order == old_order)
						item.order = new_order;
				}
				std::sort(
					layer.items.begin(), layer.items.end(),
					[](RenderItem2D& a, RenderItem2D& b)
					{ return a.order < b.order; }
				);
				return;
			}
		}
	}
}
