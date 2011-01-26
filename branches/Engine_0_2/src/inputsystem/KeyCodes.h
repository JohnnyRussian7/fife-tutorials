/**********************************************************************
*	Filename: KeyCodes.h
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
#ifndef KEYCODES_H_
#define KEYCODES_H_

// enumeration for mouse modifiers
struct MouseModifiers
{
    enum Enum
    {
        Ctrl = 1 << 0,
        Shift = 1 << 1
    };
};

struct MouseButtons
{
    enum Enum
    {
        LeftButton = 1 << 0,    // MK_LBUTTON The left mouse button is down.
        RightButton = 1 << 1,   // MK_RBUTTON The right mouse button is down. 
        MiddleButton = 1 << 2,  // MK_MBUTTON The middle mouse button is down.
        ExtraButton1 = 1 << 3,  // MK_XBUTTON1 The first X button is down.
        ExtraButton2 = 1 << 4,   // MK_XBUTTON2 The second X button is down.

        Any = -1
    };
};

// enumeration of key modifiers
struct KeyModifiers
{
    enum Enum
    {
        Ctrl    = 1 << 0,
        Alt     = 1 << 1,
        Shift   = 1 << 2
    };
};

// key codes taken from: http://msdn.microsoft.com/en-us/library/dd375731%28v=vs.85%29.aspx
struct KeyCodes
{
    enum Enum
    {
        LMouseButton = 0x01,    // VK_LBUTTON Left mouse button
        RMouseButton = 0x02,    // VK_RBUTTON Right mouse button
        Cancel = 0x03,          // VK_CANCEL Control-break processing
        MMouseButton = 0x04,    // VK_MBUTTON Middle mouse button (three-button mouse)
        X1MouseButton = 0x05,   // VK_XBUTTON1 X1 mouse button
        X2MouseButton = 0x06,   // VK_XBUTTON2 X2 mouse button
        Backspace = 0x08,       // VK_BACK BACKSPACE key
        Tab = 0x09,             // VK_TAB TAB key
        Clear = 0x0C,           // VK_CLEAR CLEAR key
        Enter = 0x0D,           // VK_RETURN ENTER key
        Shift = 0x10,           // VK_SHIFT SHIFT key
        Ctrl = 0x11,            // VK_CONTROL CTRL key
        Alt = 0x12,             // VK_MENU ALT key
        Pause = 0x13,           // VK_PAUSE PAUSE key
        CapsLock = 0x14,        // VK_CAPITAL CAPS LOCK key
        Kana = 0x15,            // VK_KANA IME Kana mode
        Hanguel = 0x15,         // VK_HANGUEL IME Hanguel mode (maintained for compatibility; use VK_HANGUL)
        Hangul = 0x15,          // VK_HANGUL IME Hangul mode
        Junja = 0x17,           // VK_JUNJA IME Junja mode
        Final = 0x18,           // VK_FINAL IME final mode
        Hanja = 0x19,           // VK_HANJA IME Hanja mode
        Kanji = 0x19,           // VK_KANJI IME Kanji mode
        Escape = 0x1B,          // VK_ESCAPE ESC key
        Convert = 0x1C,         // VK_CONVERT IME convert 
        NonConvert = 0x1D,      // VK_NONCONVERT IME nonconvert
        Accept = 0x1E,          // VK_ACCEPT IME accept
        ModeChange = 0x1F,      // VK_MODECHANGE IME mode change request
        Space = 0x20,           // VK_SPACE SPACEBAR
        Prior = 0x21,           // VK_PRIOR PAGE UP key
        Next = 0x22,            // VK_NEXT PAGE DOWN key
        End = 0x23,             // VK_END END key
        Home = 0x24,            // VK_HOME HOME key
        Left = 0x25,            // VK_LEFT LEFT ARROW key
        Up = 0x26,              // VK_UP UP ARROW key
        Right = 0x27,           // VK_RIGHT RIGHT ARROW key
        Down = 0x28,            // VK_DOWN DOWN ARROW key
        Select = 0x29,          // VK_SELECT SELECT key
        Print = 0x2A,           // VK_PRINT PRINT key
        Execute = 0x2B,         // VK_EXECUTE EXECUTE key
        Snapshot = 0x2C,        // VK_SNAPSHOT PRINT SCREEN key
        Insert = 0x2D,          // VK_INSERT INS key
        Delete = 0x2E,          // VK_DELETE DEL key
        Help = 0x2F,            // VK_HELP HELP key
        Key0 = 0x30,            // 0 key
        Key1 = 0x31,            // 1 key
        Key2 = 0x32,            // 2 key
        Key3 = 0x33,            // 3 key
        Key4 = 0x34,            // 4 key
        Key5 = 0x35,            // 5 key
        Key6 = 0x36,            // 6 key
        Key7 = 0x37,            // 7 key
        Key8 = 0x38,            // 8 key
        Key9 = 0x39,            // 9 key
        KeyA = 0x41,            // A key
        KeyB = 0x42,            // B key
        KeyC = 0x43,            // C key
        KeyD = 0x44,            // D key
        KeyE = 0x45,            // E key
        KeyF = 0x46,            // F key
        KeyG = 0x47,            // G key
        KeyH = 0x48,            // H key
        KeyI = 0x49,            // I key
        KeyJ = 0x4A,            // J key
        KeyK = 0x4B,            // K key
        KeyL = 0x4C,            // L key
        KeyM = 0x4D,            // M key
        KeyN = 0x4E,            // N key
        KeyO = 0x4F,            // O key
        KeyP = 0x50,            // P key
        KeyQ = 0x51,            // Q key
        KeyR = 0x52,            // R key
        KeyS = 0x53,            // S key
        KeyT = 0x54,            // T key
        KeyU = 0x55,            // U key
        KeyV = 0x56,            // V key
        KeyW = 0x57,            // W key
        KeyX = 0x58,            // X key
        KeyY = 0x59,            // Y key
        KeyZ = 0x5A,            // Z key
        LWindow = 0x5B,         // VK_LWIN Left Windows key (Natural keyboard)
        RWindow = 0x5C,         // VK_RWIN Right Windows key (Natural keyboard)
        Apps = 0x5D,            // VK_APPS Applications key (Natural keyboard)
        Sleep = 0x5F,           // VK_SLEEP Computer Sleep key
        Numpad0 = 0x60,         // VK_NUMPAD0 Numeric keypad 0 key
        Numpad1 = 0x61,         // VK_NUMPAD1 Numeric keypad 1 key
        Numpad2 = 0x62,         // VK_NUMPAD2 Numeric keypad 2 key
        Numpad3 = 0x63,         // VK_NUMPAD3 Numeric keypad 3 key
        Numpad4 = 0x64,         // VK_NUMPAD4 Numeric keypad 4 key
        Numpad5 = 0x65,         // VK_NUMPAD5 Numeric keypad 5 key
        Numpad6 = 0x66,         // VK_NUMPAD6 Numeric keypad 6 key   
        Numpad7 = 0x67,         // VK_NUMPAD7 Numeric keypad 7 key
        Numpad8 = 0x68,         // VK_NUMPAD8 Numeric keypad 8 key      
        Numpad9 = 0x69,         // VK_NUMPAD9 Numeric keypad 9 key   
        Multiply = 0x6A,        // VK_MULTIPLY Multiply key 
        Add = 0x6B,             // VK_ADD Add key
        Separator = 0x6C,       // VK_SEPARATOR Separator key
        Subtract = 0x6D,        // VK_SUBTRACT Subtract key
        Decimal = 0x6E,         // VK_DECIMAL Decimal key
        Divide = 0x6F,          // VK_DIVIDE Divide key
        F1 = 0x70,              // VK_F1 F1 key
        F2 = 0x71,              // VK_F2 F2 key 
        F3 = 0x72,              // VK_F3 F3 key
        F4 = 0x73,              // VK_F4 F4 key
        F5 = 0x74,              // VK_F5 F5 key
        F6 = 0x75,              // VK_F6 F6 key
        F7 = 0x76,              // VK_F7 F7 key
        F8 = 0x77,              // VK_F8 F8 key
        F9 = 0x78,              // VK_F9 F9 key
        F10 = 0x79,             // VK_F10 F10 key
        F11 = 0x7A,             // VK_F11 F11 key
        F12 = 0x7B,             // VK_F12 F12 key
        F13 = 0x7C,             // VK_F13 F13 key
        F14 = 0x7D,             // VK_F14 F14 key
        F15 = 0x7E,             // VK_F15 F15 key
        F16 = 0x7F,             // VK_F16 F16 key
        F17 = 0x80,             // VK_F17 F17 key
        F18 = 0x81,             // VK_F18 F18 key
        F19 = 0x82,             // VK_F19 F19 key
        F20 = 0x83,             // VK_F20 F20 key
        F21 = 0x84,             // VK_F21 F21 key
        F22 = 0x85,             // VK_F22 F22 key
        F23 = 0x86,             // VK_F23 F23 key
        F24 = 0x87,             // VK_F24 F24 key
        NumLock = 0x90,         // VK_NUMLOCK NUM LOCK key
        Scroll = 0x91,          // VK_SCROLL SCROLL LOCK key
        LShift = 0xA0,          // VK_LSHIFT Left SHIFT key
        RShift = 0xA1,          // VK_RSHIFT Right SHIFT key
        LCtrl = 0xA2,           // VK_LCONTROL Left CONTROL key
        RCtrl = 0xA3,           // VK_RCONTROL Right CONTROL key
        LAlt = 0xA4,            // VK_LMENU Left MENU key
        RAlt = 0xA5,            // VK_RMENU Right MENU key
        BrowserBack = 0xA6,     // VK_BROWSER_BACK Browser Back key
        BrowserForward = 0xA7,  // VK_BROWSER_FORWARD Browser Forward key
        BrowserRefresh = 0xA8,  // VK_BROWSER_REFRESH Browser Refresh key
        BrowserStop = 0xA9,     // VK_BROWSER_STOP Browser Stop key
        BrowserSearch = 0xAA,   // VK_BROWSER_SEARCH Browser Search key
        BrowserFav = 0xAB,      // VK_BROWSER_FAVORITES Browser Favorites key
        BrowserHome = 0xAC,     // VK_BROWSER_HOME Browser Start and Home key
        VolumeMute = 0xAD,      // VK_VOLUME_MUTE Volume Mute key
        VolumeDown = 0xAE,      // VK_VOLUME_DOWN Volume Down key
        VolumeUp = 0xAF,        // VK_VOLUME_UP Volume Up key
        NextTrack = 0xB0,       // VK_MEDIA_NEXT_TRACK Next Track key
        PreviousTrack = 0xB1,   // VK_MEDIA_PREV_TRACK Previous Track key
        MediaStop = 0xB2,       // VK_MEDIA_STOP Stop Media key
        MediaPlayPause = 0xB3,  // VK_MEDIA_PLAY_PAUSE Play/Pause Media key
        LaunchMail = 0xB4,      // VK_LAUNCH_MAIL Start Mail key
        LaunchMedia = 0xB5,     // VK_LAUNCH_MEDIA_SELECT Select Media key
        LaunchApp1 = 0xB6,      // VK_LAUNCH_APP1 Start Application 1 key
        LaunchApp2 = 0xB7,      // VK_LAUNCH_APP2 Start Application 2 key
        Oem1 = 0xBA,            // VK_OEM_1 Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ';:' key
        Plus = 0xBB,            // VK_OEM_PLUS For any country/region, the '+' key
        Comma = 0xBC,           // VK_OEM_COMMA For any country/region, the ',' key
        Minus = 0xBD,           // VK_OEM_MINUS For any country/region, the '-' key
        Period = 0xBE,          // VK_OEM_PERIOD For any country/region, the '.' key       
        Oem2 = 0xBF,            // VK_OEM_2 Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key
        Oem3 = 0xC0,            // VK_OEM_3 Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key
        Oem4 = 0xDB,            // VK_OEM_4 Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key
        Oem5 = 0xDC,            // VK_OEM_5 Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\|' key
        Oem6 = 0xDD,            // VK_OEM_6 Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key
        Oem7 = 0xDE,            // VK_OEM_7 Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key
        Oem8 = 0xDF,            // VK_OEM_8  Used for miscellaneous characters; it can vary by keyboard.
        Oem102 = 0xE2,          // VK_OEM_102 Either the angle bracket key or the backslash key on the RT 102-key keyboard
        Process = 0xE5,         // VK_PROCESSKEY IME PROCESS key
        OemSpecific = 0xE6,     // OEM specific
        Packet = 0xE7,          // VK_PACKET Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP
        Attn = 0xF6,            // VK_ATTN Attn key
        CrSel = 0xF7,           // VK_CRSEL CrSel key
        ExSel = 0xF8,           // VK_EXSEL ExSel key
        EraseEOF = 0xF9,        // VK_EREOF Erase EOF key
        Play = 0xFA,            // VK_PLAY Play key
        Zoom = 0xFB,            // VK_ZOOM Zoom key
        Noname = 0xFC,          // VK_NONAME Reserved
        Pa1 = 0xFD,             // VK_PA1 PA1 key
        OemClear = 0xFE,        // VK_OEM_CLEAR Clear key
   };
};

#endif
