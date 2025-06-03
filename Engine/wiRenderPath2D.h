#pragma once
#include "wiRenderPath.h"
#include "wiGUI.h"
#include "wiVector.h"

#include <string>

namespace wi
{
	class Sprite;
	class SpriteFont;

	class RenderPath2D :
		public RenderPath
	{
	protected:
		wi::graphics::Texture rtStencilExtracted;
		wi::graphics::Texture stencilScaled;

		wi::graphics::Texture rtFinal;
		wi::graphics::Texture rtFinal_MSAA;

		wi::gui::GUI GUI;

		XMUINT2 current_buffersize{};
		float current_layoutscale{};

		float hdr_scaling = 9.0f;

		uint32_t msaaSampleCount = 1;
		uint32_t msaaSampleCount2D = 1;

	public:
		// Delete GPU resources and initialize them to default
		virtual void DeleteGPUResources();
		// create resolution dependent resources, such as render targets
		virtual void ResizeBuffers();
		// update DPI dependent elements, such as GUI elements, sprites
		virtual void ResizeLayout();

		void Update(float dt) override;
		void FixedUpdate() override;
		void PreRender() override;
		void Render() const override;
		void Compose(wi::graphics::CommandList cmd) const override;

		virtual void setMSAASampleCount(uint32_t value) { msaaSampleCount = value; }
		constexpr uint32_t getMSAASampleCount() const { return msaaSampleCount; }

		virtual void setMSAASampleCount2D(uint32_t value) { msaaSampleCount2D = value; }
		constexpr uint32_t getMSAASampleCount2D() const { return msaaSampleCount2D; }

		const wi::graphics::Texture& GetRenderResult() const { return rtFinal; }
		virtual const wi::graphics::Texture* GetDepthStencil() const { return nullptr; }
		virtual const wi::graphics::Texture* GetGUIBlurredBackground() const { return nullptr; }

		void AddSprite(wi::Sprite* sprite, const std::string& layer = "", const int order = 0);
		inline void AddSprite(wi::Sprite* sprite, const int order)
		{ AddSprite(sprite, "", order); }

		template <class InputIterator>
		void AddSprites(InputIterator first, InputIterator last, const std::string& layer_name = "", const int order = 0)
		{
			for (auto& layer : layers)
			{
				RenderItem2D item{};
				item.type  = RenderItem2D::TYPE::SPRITE;
				item.order = order;
				if (layer.name.compare(layer_name) == 0)
				{
					layer.items.reserve(std::distance(first, last));
					for (auto it = first; it != last; ++it)
					{
						item.sprite = &(*it);
						layer.items.push_back(item);
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
		template <class InputIterator>
		inline void AddSprites(InputIterator first, InputIterator last, const int order)
		{ AddSprites(first, last, "", order); }

		void RemoveSprite(wi::Sprite* sprite);
		void ClearSprites();
		int GetSpriteOrder(wi::Sprite* sprite);

		void AddFont(wi::SpriteFont* font, const std::string& layer = "", const int order = 0);
		inline void AddFont(wi::SpriteFont* font, const int order)
		{ AddFont(font, "", order); SortLayers(); }

		template <class InputIterator>
		void AddFonts(InputIterator first, InputIterator last, const std::string& layer_name = "", const int order = 0)
		{
			for (auto& layer : layers)
			{
				RenderItem2D item{};
				item.type  = RenderItem2D::TYPE::FONT;
				item.order = order;
				if (layer.name.compare(layer_name) == 0)
				{
					layer.items.reserve(std::distance(first, last));
					for (auto it = first; it != last; ++it)
					{
						item.font = &(*it);
						layer.items.push_back(item);
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

		template <class InputIterator>
		inline void AddFonts(InputIterator first, InputIterator last, const int order)
		{ AddFonts(first, last, "", order); }

		void RemoveFont(wi::SpriteFont* font);
		void ClearFonts();
		int GetFontOrder(wi::SpriteFont* font);

		void RemoveRenderObjects(const std::string& layer_name, const int order);
		void ChangeRenderOrder(const std::string& layer_name, const int old_order, const int new_order);

		struct RenderItem2D
		{
			enum class TYPE
			{
				SPRITE,
				FONT,
			} type = TYPE::SPRITE;
			union
			{
				wi::Sprite* sprite = nullptr;
				wi::SpriteFont* font;
			};
			int order = 0;
		};
		struct RenderLayer2D
		{
			wi::vector<RenderItem2D> items;
			std::string name;
			int order = 0;
		};
		wi::vector<RenderLayer2D> layers{ 1 };
		void AddLayer(const std::string& name, int order = 0);
		void SetLayerOrder(const std::string& name, int order);
		void SetSpriteOrder(wi::Sprite* sprite, int order);
		void SetFontOrder(wi::SpriteFont* font, int order);
		void SortLayers();
		void CleanLayers();

		const wi::gui::GUI& GetGUI() const { return GUI; }
		wi::gui::GUI& GetGUI() { return GUI; }

		float resolutionScale = 1.0f;
		XMUINT2 GetInternalResolution() const
		{
			return XMUINT2(
				uint32_t((float)GetPhysicalWidth() * resolutionScale),
				uint32_t((float)GetPhysicalHeight() * resolutionScale)
			);
		}

		float GetHDRScaling() const { return hdr_scaling; }
		void SetHDRScaling(float value) { hdr_scaling = value; }
	};

}
