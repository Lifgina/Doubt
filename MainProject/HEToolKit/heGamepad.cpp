#include "heGamePad.h"
#include "heRawGamepad.h"

#include "CommonInclude.h"
#include "wiPlatform.h"
#include "wiXInput.h"
#include "wiHelper.h"
#include "wiBacklog.h"
#include "wiProfiler.h"
#include "wiTimer.h"
#include "wiColor.h"
#include "wiVector.h"

#include <algorithm>
#include <atomic>


namespace wi::input {
	extern wi::vector<Controller> controllers;
	extern std::atomic_bool initialized;
}

namespace he::gamepad
{
	wi::vector<uint32_t> pressed;
	wi::vector<uint32_t> released;

	void Initialize()
	{
		wi::Timer timer;

		he::rawgamepad::Initialize();

		wi::backlog::post("he::gamepad Initialized (" + std::to_string((int)std::round(timer.elapsed())) + " ms)");
		wi::input::initialized.store(true);
	}

	void Update()
	{
		auto range = wi::profiler::BeginRangeCPU("GamePad");

		wi::input::xinput::Update();
		he::rawgamepad::Update();

		// Check if low-level XINPUT controller is not registered for playerindex slot and register:
		for (int i = 0; i < wi::input::xinput::GetMaxControllerCount(); ++i)
		{
			if (wi::input::xinput::GetControllerState(nullptr, i))
			{
				int slot = -1;
				for (int j = 0; j < (int)wi::input::controllers.size(); ++j)
				{
					if (slot < 0 && wi::input::controllers[j].deviceType == wi::input::Controller::DISCONNECTED)
					{
						// take the first disconnected slot
						slot = j;
					}
					if (wi::input::controllers[j].deviceType == wi::input::Controller::XINPUT && wi::input::controllers[j].deviceIndex == i)
					{
						// it is already registered to this slot
						slot = j;
						break;
					}
				}
				if (slot == -1)
				{
					// no disconnected slot was found, and it was not registered
					slot = (int)wi::input::controllers.size();
					wi::input::controllers.emplace_back();

					pressed .emplace_back();
					released.emplace_back();
				}
				wi::input::controllers[slot].deviceType = wi::input::Controller::XINPUT;
				wi::input::controllers[slot].deviceIndex = i;
			}
		}

		// Check if low-level RAWINPUT controller is not registered for playerindex slot and register:
		for (int i = 0; i < he::rawgamepad::GetMaxControllerCount(); ++i)
		{
			if (he::rawgamepad::GetControllerState(nullptr, i))
			{
				int slot = -1;
				for (int j = 0; j < (int)wi::input::controllers.size(); ++j)
				{
					if (slot < 0 && wi::input::controllers[j].deviceType == wi::input::Controller::DISCONNECTED)
					{
						// take the first disconnected slot
						slot = j;
					}
					if (wi::input::controllers[j].deviceType == wi::input::Controller::RAWINPUT && wi::input::controllers[j].deviceIndex == i)
					{
						// it is already registered to this slot
						slot = j;
						break;
					}
				}
				if (slot == -1)
				{
					// no disconnected slot was found, and it was not registered
					slot = (int)wi::input::controllers.size();
					wi::input::controllers.emplace_back();

					pressed .emplace_back();
					released.emplace_back();
				}
				wi::input::controllers[slot].deviceType = wi::input::Controller::RAWINPUT;
				wi::input::controllers[slot].deviceIndex = i;
			}
		}

		// Read low-level controllers:
		for (int i = 0; i < wi::input::controllers.size(); ++i)
		{
			const uint32_t state = wi::input::controllers[i].state.buttons;
			bool connected = false;
			switch (wi::input::controllers[i].deviceType)
			{
			case wi::input::Controller::XINPUT:
				connected = wi::input::xinput::GetControllerState(&wi::input::controllers[i].state, wi::input::controllers[i].deviceIndex);
				break;
			case wi::input::Controller::RAWINPUT:
				connected = he::rawgamepad::GetControllerState(&wi::input::controllers[i].state, wi::input::controllers[i].deviceIndex);
				break;
			}

			if (connected)
			{
				pressed [i] = ~state &  wi::input::controllers[i].state.buttons;
				released[i] =  state & ~wi::input::controllers[i].state.buttons;
			}
			else
			{
				wi::input::controllers[i].deviceType = wi::input::Controller::DISCONNECTED;
				pressed [i] = 0;
				released[i] = 0;
			}
		}

		//for (auto& controller : wi::input::controllers)
		//{
		//	bool connected = false;
		//	switch (controller.deviceType)
		//	{
		//		case wi::input::Controller::XINPUT:
		//			connected = wi::input::xinput::GetControllerState(&controller.state, controller.deviceIndex);
		//			break;
		//		case wi::input::Controller::RAWINPUT:
		//			connected = he::rawgamepad::GetControllerState(&controller.state, controller.deviceIndex);
		//			break;
		//	}

		//	if (!connected)
		//	{
		//		controller.deviceType = wi::input::Controller::DISCONNECTED;
		//	}
		//}

		wi::profiler::EndRange(range);
	}

	wi::vector<wi::input::Controller>& GetGamepadState()
	{
		return wi::input::controllers;
	}

	wi::vector<uint32_t>& GetGamepadPressed()
	{
		return he::gamepad::pressed;
	}

	wi::vector<uint32_t>& GetGamepadReleased()
	{
		return he::gamepad::released;
	}
}
