#pragma once

#include "WickedEngine.h"
#include "HEMathematics.h"

namespace HE = wi;
namespace wi {
	namespace Audio     = audio;
	namespace ECS       = ecs;
	namespace Enums     = enums;
	namespace Font      = font;
	namespace JobSystem = jobsystem;
	namespace Lua       = lua;
	namespace Network   = network;
	namespace Primitive = primitive;
	namespace Random    = random;
	namespace Renderer  = renderer;
	namespace Scene3D   = scene;

	namespace ResourceManager = resourcemanager;

	inline DWORD GetDisplayFrequency()
	{
		DEVMODE dm;
		::EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dm);
		return dm.dmDisplayFrequency;
	}

	namespace jobsystem {
		typedef context Context;
	}

	namespace scene {
		typedef primitive::Ray Ray;
		typedef PickResult RaycastHit;

		//inline RaycastHit Raycast(const Ray& ray, uint32_t renderTypeMask = wi::enums::RENDERTYPE_OPAQUE, uint32_t layerMask = ~0, const Scene& scene = GetScene())
		//{ return Scene3D::Pick(ray, renderTypeMask, layerMask, scene); }

		//bool  Raycast(XMFLOAT3 origin, XMFLOAT3 direction, float maxDistance, const uint32_t layerMask = ~0, const Scene& scene = GetScene());
		//float Raycast(XMFLOAT3 origin, XMFLOAT3 direction, const uint32_t layerMask = ~0, const Scene& scene = GetScene());

		inline uint32_t LayerMask(const int mask) { return 1U << mask; }
		inline uint32_t LayerMaskInverse(const int mask) { return ~(1U << mask); }

		inline void SetLayerMask(const uint32_t layerMask)
		{
			const auto& scene = GetScene();
			for (size_t i = 0; i < scene.layers.GetCount(); ++i)
				scene.layers[i].layerMask = layerMask;
		}

		HE::ECS::Entity LoadModel(Scene& scene, const std::string& fileName, const uint32_t layerMask, const XMMATRIX& transformMatrix = XMMatrixIdentity(), bool attached = false);
		inline HE::ECS::Entity LoadModel(const std::string& fileName, const uint32_t layerMask, const XMMATRIX& transformMatrix = XMMatrixIdentity(), bool attached = false)
		{ return LoadModel(GetScene(), fileName, layerMask, transformMatrix, attached); }
	}

	class Scene : public RenderPath3D {
	public:
		Scene() = default;
		virtual ~Scene() = default;

		virtual void Initialize() = 0;
		virtual void Terminate() = 0;
	};

	class Sound {
	public:
		enum class LoopCount {
			BGM = 255,
			SE  = 0
		};
		enum {
			PlayCount = -1
		};

		Sound() = default;

		Sound(const std::string& filename, const int loop_count)
		{
			if (!Audio::CreateSound(filename, &sound))
				return;
			Audio::CreateSoundInstance(&sound, &sound_instance, loop_count);
		}
		Sound(const std::string& filename, const LoopCount loop_count)
		{
			if (!Audio::CreateSound(filename, &sound))
				return;
			Audio::CreateSoundInstance(&sound, &sound_instance, (int)loop_count);
		}

		inline void Play() { Audio::Play(&sound_instance); }
		inline void Pause() { Audio::Pause(&sound_instance); }
		inline void Stop() { Audio::Stop(&sound_instance); }

		inline void PlayFromTop()
		{
			Audio::Stop(&sound_instance);
			Audio::Play(&sound_instance);
		}

		inline bool isPlaying()  { return Audio::isPlaying(&sound_instance); }
		//inline bool isFinished() { return Audio::IsEnded(&sound_instance); }

		inline void  SetVolume(float volume) { Audio::SetVolume(volume, &sound_instance); }
		inline float GetVolume() { return Audio::GetVolume(&sound_instance); }

	private:
		Audio::Sound         sound;
		Audio::SoundInstance sound_instance;
	};

	struct TIME {
		float deltaTime;
		float time;
		long long frameCount;
	};
}

extern HE::RenderPath2D*             RenderingPath;
extern HE::Scene3D::Scene&           DefaultScene;
extern HE::Scene3D::CameraComponent* MainCamera;
extern HE::TIME Time;