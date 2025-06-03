#pragma once

#include "wiInput.h"

namespace wi::input {
	struct Controller
	{
		enum DeviceType
		{
			DISCONNECTED,
			XINPUT,
			RAWINPUT,
			SDLINPUT,
		};
		DeviceType deviceType;
		int deviceIndex;
		ControllerState state;
	};
}

namespace he::gamepad
{
	// call once at app start
	void Initialize();

	// call once per frame
	void Update();

	wi::vector<wi::input::Controller>& GetGamepadState();
	wi::vector<uint32_t>& GetGamepadPressed();
	wi::vector<uint32_t>& GetGamepadReleased();
};

