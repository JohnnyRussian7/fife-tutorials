/**********************************************************************
 *	Filename: OsxKeyConverter.cpp
 *	
 *	Copyright (C) 2010, FIFE team
 *	http://www.fifengine.net
 *
 *	This file is part of FIFE.
 *
 *	FIFE is free software: you can redistribute it and/or modify it
 *	under the terms of the GNU Lesser General Public License as
 *	published by the Free Software Foundation, either version 3 of
 *	the License, or any later version.
 *
 *	FIFE is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with FIFE. If not, see http://www.gnu.org/licenses/.
 ***********************************************************************/
#include "PrecompiledIncludes.h"

#include <Carbon/Carbon.h>

#include "OsxKeyConverter.h"

KeyCodes::Enum ConvertOsxVirtualKeyToKeyCode(uint16_t virtualKey)
{
    switch (virtualKey)
    {
        case kVK_ANSI_A:
            return KeyCodes::KeyA;
        case kVK_ANSI_S:
            return KeyCodes::KeyS;
        case kVK_ANSI_D:
            return KeyCodes::KeyD;
        case kVK_ANSI_F:
            return KeyCodes::KeyF;
        case kVK_ANSI_H:
            return KeyCodes::KeyH;
        case kVK_ANSI_G:
            return KeyCodes::KeyG;
        case kVK_ANSI_Z:
            return KeyCodes::KeyZ;
        case kVK_ANSI_X:
            return KeyCodes::KeyX;
        case kVK_ANSI_C:
            return KeyCodes::KeyC;
        case kVK_ANSI_V:
            return KeyCodes::KeyV;
        case kVK_ANSI_B:
            return KeyCodes::KeyB;
        case kVK_ANSI_Q:
            return KeyCodes::KeyQ;
        case kVK_ANSI_W:
            return KeyCodes::KeyW;
        case kVK_ANSI_E:
            return KeyCodes::KeyE;
        case kVK_ANSI_R:
            return KeyCodes::KeyR;
        case kVK_ANSI_Y:
            return KeyCodes::KeyY;
        case kVK_ANSI_T:
            return KeyCodes::KeyT;
        case kVK_ANSI_1:
            return KeyCodes::Key1;
        case kVK_ANSI_2:
            return KeyCodes::Key2;
        case kVK_ANSI_3:
            return KeyCodes::Key3;
        case kVK_ANSI_4:
            return KeyCodes::Key4;
        case kVK_ANSI_6:
            return KeyCodes::Key6;
        case kVK_ANSI_5:
            return KeyCodes::Key5;
        case kVK_ANSI_Equal:
            return KeyCodes::Plus;
        case kVK_ANSI_9:
            return KeyCodes::Key9;
        case kVK_ANSI_7:
            return KeyCodes::Key7;
        case kVK_ANSI_Minus:
            return KeyCodes::Minus;
        case kVK_ANSI_8:
            return KeyCodes::Key8;
        case kVK_ANSI_0:
            return KeyCodes::Key0;
        case kVK_ANSI_RightBracket:
            return KeyCodes::Oem6;
        case kVK_ANSI_O:
            return KeyCodes::KeyO;
        case kVK_ANSI_U:
            return KeyCodes::KeyU;
        case kVK_ANSI_LeftBracket:
            return KeyCodes::Oem4;
        case kVK_ANSI_I:
            return KeyCodes::KeyI;
        case kVK_ANSI_P:
            return KeyCodes::KeyP;
        case kVK_ANSI_L:
            return KeyCodes::KeyL;
        case kVK_ANSI_J:
            return KeyCodes::KeyJ;
        case kVK_ANSI_Quote:
            return KeyCodes::Oem7;
        case kVK_ANSI_K:
            return KeyCodes::KeyK;
        case kVK_ANSI_Semicolon:
            return KeyCodes::Oem1;
        case kVK_ANSI_Backslash:
            return KeyCodes::Oem5;
        case kVK_ANSI_Comma:
            return KeyCodes::Comma;
        case kVK_ANSI_Slash:
            return KeyCodes::Oem2;
        case kVK_ANSI_N:
            return KeyCodes::KeyN;
        case kVK_ANSI_M:
            return KeyCodes::KeyM;
        case kVK_ANSI_Period:
            return KeyCodes::Period;
        case kVK_ANSI_Grave:
            return KeyCodes::Oem3;
        case kVK_ANSI_KeypadDecimal:
            return KeyCodes::Decimal;
        case kVK_ANSI_KeypadMultiply:
            return KeyCodes::Multiply;
        case kVK_ANSI_KeypadPlus:
            return KeyCodes::Add;
        case kVK_ANSI_KeypadClear:
            return KeyCodes::NumLock;
        case kVK_ANSI_KeypadDivide:
            return KeyCodes::Divide;
        case kVK_ANSI_KeypadEnter:
            return KeyCodes::Enter;     //TODO - this will need to be changed once ENTER and NUMPAD_ENTER
                                        //       are different enumerations
        case kVK_ANSI_KeypadMinus:
            return KeyCodes::Subtract;
        case kVK_ANSI_KeypadEquals:
            // TODO need enumeration for this, for now use enum for (+,=)
            return KeyCodes::Plus;
        case kVK_ANSI_Keypad0:
            return KeyCodes::Numpad0;
        case kVK_ANSI_Keypad1:
            return KeyCodes::Numpad1;
        case kVK_ANSI_Keypad2:
            return KeyCodes::Numpad2;
        case kVK_ANSI_Keypad3:
            return KeyCodes::Numpad3;
        case kVK_ANSI_Keypad4:
            return KeyCodes::Numpad4;
        case kVK_ANSI_Keypad5:
            return KeyCodes::Numpad5;
        case kVK_ANSI_Keypad6:
            return KeyCodes::Numpad6;
        case kVK_ANSI_Keypad7:
            return KeyCodes::Numpad7;
        case kVK_ANSI_Keypad8:
            return KeyCodes::Numpad8;
        case kVK_ANSI_Keypad9:
            return KeyCodes::Numpad9;
        case kVK_Return:
            return KeyCodes::Enter;
        case kVK_Tab:
            return KeyCodes::Tab;
        case kVK_Space:
            return KeyCodes::Space;
        case kVK_Delete:
            return KeyCodes::Backspace;
        case kVK_Escape:
            return KeyCodes::Escape;
        case kVK_Command:
            // TODO - figure out if mapping apple command key to control
            //        is the right thing to do
            return KeyCodes::Ctrl;
        case kVK_Shift:
            return KeyCodes::LShift;
        case kVK_CapsLock:
            return KeyCodes::CapsLock;
        case kVK_Option:
            return KeyCodes::LAlt;
        case kVK_Control:
            return KeyCodes::LCtrl;
        case kVK_RightShift:
            return KeyCodes::RShift;
        case kVK_RightOption:
            return KeyCodes::RAlt;
        case kVK_RightControl:
            return KeyCodes::RCtrl;
        
        // TODO - need to add enumeration for Function
        //kVK_Function                  = 0x3F,
        
        case kVK_F17:
            return KeyCodes::F17;
        case kVK_VolumeUp:
            return KeyCodes::VolumeUp;
        case kVK_VolumeDown:
            return KeyCodes::VolumeDown;
        case kVK_Mute:
            return KeyCodes::VolumeMute;
        case kVK_F18:
            return KeyCodes::F18;
        case kVK_F19:
            return KeyCodes::F19;
        case kVK_F20:
            return KeyCodes::F20;
        case kVK_F5:
            return KeyCodes::F5;
        case kVK_F6:
            return KeyCodes::F6;
        case kVK_F7:
            return KeyCodes::F7;
        case kVK_F3:
            return KeyCodes::F3;
        case kVK_F8:
            return KeyCodes::F8;
        case kVK_F9:
            return KeyCodes::F9;
        case kVK_F11:
            return KeyCodes::F11;
        case kVK_F13:
            return KeyCodes::F13;
        case kVK_F16:
            return KeyCodes::F16;
        case kVK_F14:
            return KeyCodes::F14;
        case kVK_F10:
            return KeyCodes::F10;
        case kVK_F12:
            return KeyCodes::F12;
        case kVK_F15:
            return KeyCodes::F15;
        case kVK_Help:
            return KeyCodes::Help;
        case kVK_Home:
            return KeyCodes::Home;
        case kVK_PageUp:
            return KeyCodes::Prior;
        case kVK_ForwardDelete:
            return KeyCodes::Delete;
        case kVK_F4:
            return KeyCodes::F4;
        case kVK_End:
            return KeyCodes::End;
        case kVK_F2:
            return KeyCodes::F2;
        case kVK_PageDown:
            return KeyCodes::Next;
        case kVK_F1:
            return KeyCodes::F1;
        case kVK_LeftArrow:
            return KeyCodes::Left;
        case kVK_RightArrow:
            return KeyCodes::Right;
        case kVK_DownArrow:
            return KeyCodes::Down;
        case kVK_UpArrow:
            return KeyCodes::Up;
        default:
            return KeyCodes::Invalid;
	}
	
    // TODO - currently not supported
    /*
	// ISO keyboards only
	enum {
        kVK_ISO_Section               = 0x0A
	};
	
	// JIS keyboards only
	enum {
        kVK_JIS_Yen                   = 0x5D,
        kVK_JIS_Underscore            = 0x5E,
        kVK_JIS_KeypadComma           = 0x5F,
        kVK_JIS_Eisu                  = 0x66,
        kVK_JIS_Kana                  = 0x68
	};
    */
}