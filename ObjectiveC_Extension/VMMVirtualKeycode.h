/*
 *  Summary:
 *    Virtual keycodes
 *
 *  Discussion:
 *    These constants are the virtual keycodes defined originally in
 *    Inside Mac Volume V, pg. V-191. They identify physical keys on a
 *    keyboard. Those constants with "ANSI" in the name are labeled
 *    according to the key position on an ANSI-standard US keyboard.
 *    For example, kVK_ANSI_A indicates the virtual keycode for the key
 *    with the letter 'A' in the US keyboard layout. Other keyboard
 *    layouts may have the 'A' key label on a different physical key;
 *    in this case, pressing 'A' will generate a different virtual
 *    keycode.
 */
// http://stackoverflow.com/a/16125341/4370893
//
// Power Mac Keypad Enter / iBook Enter Key (0x34):
// https://bugs.chromium.org/p/chromium/issues/detail?id=542634
// https://www.virtualbox.org/svn/vbox/trunk/src/VBox/Frontends/VirtualBox/src/platform/darwin/DarwinKeyboard.cpp
//
// Many keys that weren't in the first references:
// http://www.insanelymac.com/forum/topic/236835-updated-2012-genericbrightnesskext/page-16
//
// Context Menu Key (0x6E):
// https://chromium.googlesource.com/chromium/src/+/lkgr/ui/events/keycodes/keyboard_code_conversion_mac.mm
//
// Spotlight (0x81), Dashboard (0x82), Launchpad (0x83):
// https://github.com/RehabMan/OS-X-Voodoo-PS2-Controller/blob/master/VoodooPS2Keyboard/VoodooPS2Keyboard.cpp
//
// Tilde (0x0A):
// https://github.com/SFML/SFML/blob/master/src/SFML/Window/OSX/HIDInputManager.mm

#import <Foundation/Foundation.h>

@interface VMMVirtualKeycode : NSObject

+(NSArray<NSString*>*)allKeyNames;

+(NSDictionary*)virtualKeycodeNames;
+(NSString*)nameOfVirtualKeycode:(CGKeyCode)key;

@end

enum {
    kVK_ANSI_A                    = 0x00,
    kVK_ANSI_S                    = 0x01,
    kVK_ANSI_D                    = 0x02,
    kVK_ANSI_F                    = 0x03,
    kVK_ANSI_H                    = 0x04,
    kVK_ANSI_G                    = 0x05,
    kVK_ANSI_Z                    = 0x06,
    kVK_ANSI_X                    = 0x07,
    kVK_ANSI_C                    = 0x08,
    kVK_ANSI_V                    = 0x09,
    kVK_ISO_Section               = 0x0A, // Not present in keycode usage? Possibly Tilde; have to test
    kVK_ANSI_B                    = 0x0B,
    kVK_ANSI_Q                    = 0x0C,
    kVK_ANSI_W                    = 0x0D,
    kVK_ANSI_E                    = 0x0E,
    kVK_ANSI_R                    = 0x0F,
    kVK_ANSI_Y                    = 0x10,
    kVK_ANSI_T                    = 0x11,
    kVK_ANSI_1                    = 0x12,
    kVK_ANSI_2                    = 0x13,
    kVK_ANSI_3                    = 0x14,
    kVK_ANSI_4                    = 0x15,
    kVK_ANSI_6                    = 0x16,
    kVK_ANSI_5                    = 0x17,
    kVK_ANSI_Equal                = 0x18,
    kVK_ANSI_9                    = 0x19,
    kVK_ANSI_7                    = 0x1A,
    kVK_ANSI_Minus                = 0x1B,
    kVK_ANSI_8                    = 0x1C,
    kVK_ANSI_0                    = 0x1D,
    kVK_ANSI_RightBracket         = 0x1E,
    kVK_ANSI_O                    = 0x1F,
    kVK_ANSI_U                    = 0x20,
    kVK_ANSI_LeftBracket          = 0x21,
    kVK_ANSI_I                    = 0x22,
    kVK_ANSI_P                    = 0x23,
    kVK_Enter                     = 0x24, /* Mac calls it Return */
    kVK_ANSI_L                    = 0x25,
    kVK_ANSI_J                    = 0x26,
    kVK_ANSI_Quote                = 0x27,
    kVK_ANSI_K                    = 0x28,
    kVK_ANSI_Semicolon            = 0x29,
    kVK_ANSI_Backslash            = 0x2A,
    kVK_ANSI_Comma                = 0x2B,
    kVK_ANSI_Slash                = 0x2C,
    kVK_ANSI_N                    = 0x2D,
    kVK_ANSI_M                    = 0x2E,
    kVK_ANSI_Period               = 0x2F,
    kVK_Tab                       = 0x30,
    kVK_Space                     = 0x31,
    kVK_ANSI_Grave                = 0x32,
    kVK_Delete                    = 0x33, /* Backspace in Windows keyboards */
    kVK_Play                      = 0x34, // Not present in keycode usage?
    kVK_Escape                    = 0x35,
    kVK_RightCommand              = 0x36,
    kVK_LeftCommand               = 0x37,
    kVK_LeftShift                 = 0x38,
    kVK_CapsLock                  = 0x39,
    kVK_LeftOption                = 0x3A,
    kVK_LeftControl               = 0x3B,
    kVK_RightShift                = 0x3C,
    kVK_RightOption               = 0x3D,
    kVK_RightControl              = 0x3E,
    kVK_Function                  = 0x3F, // Not present in keycode usage?
    kVK_F17                       = 0x40,
    kVK_ANSI_KeypadDecimal        = 0x41,
    kVK_Next                      = 0x42, // Not present in keycode usage?
    kVK_ANSI_KeypadMultiply       = 0x43,
    // 44?
    kVK_ANSI_KeypadPlus           = 0x45,
    // 46?
    kVK_ANSI_KeypadClear          = 0x47, /* This is also Num Lock */
    kVK_VolumeUp                  = 0x48,
    kVK_VolumeDown                = 0x49,
    kVK_Mute                      = 0x4A,
    kVK_ANSI_KeypadDivide         = 0x4B,
    kVK_ANSI_KeypadEnter          = 0x4C,
    kVK_Previous                  = 0x4D, // Not present in keycode usage?
    kVK_ANSI_KeypadMinus          = 0x4E,
    kVK_F18                       = 0x4F,
    kVK_F19                       = 0x50,
    kVK_ANSI_KeypadEquals         = 0x51,
    kVK_ANSI_Keypad0              = 0x52,
    kVK_ANSI_Keypad1              = 0x53,
    kVK_ANSI_Keypad2              = 0x54,
    kVK_ANSI_Keypad3              = 0x55,
    kVK_ANSI_Keypad4              = 0x56,
    kVK_ANSI_Keypad5              = 0x57,
    kVK_ANSI_Keypad6              = 0x58,
    kVK_ANSI_Keypad7              = 0x59,
    kVK_F20                       = 0x5A,
    kVK_ANSI_Keypad8              = 0x5B,
    kVK_ANSI_Keypad9              = 0x5C,
    kVK_JIS_Yen                   = 0x5D,
    kVK_JIS_Underscore            = 0x5E, // Not present in keycode usage?
    kVK_JIS_KeypadComma           = 0x5F,
    kVK_F5                        = 0x60,
    kVK_F6                        = 0x61,
    kVK_F7                        = 0x62,
    kVK_F3                        = 0x63,
    kVK_F8                        = 0x64,
    kVK_F9                        = 0x65,
    kVK_JIS_Eisu                  = 0x66, // Not present in keycode usage?
    kVK_F11                       = 0x67,
    kVK_JIS_Kana                  = 0x68, // Not present in keycode usage?
    kVK_F13                       = 0x69,
    kVK_F16                       = 0x6A,
    kVK_F14                       = 0x6B,
    // 6C?
    kVK_F10                       = 0x6D,
    kVK_ContextMenu               = 0x6E, /* That strange key next to Alt Gr in Windows keyboards */
    kVK_F12                       = 0x6F,
    kVK_VidMirror                 = 0x70, // Not present in keycode usage? /* Toggle between extended desktop and clone mode */
    kVK_F15                       = 0x71,
    kVK_Help                      = 0x72, // Maybe Insert in different keyboard? Have to check
    kVK_Home                      = 0x73,
    kVK_PageUp                    = 0x74,
    kVK_ForwardDelete             = 0x75,
    kVK_F4                        = 0x76,
    kVK_End                       = 0x77,
    kVK_F2                        = 0x78,
    kVK_PageDown                  = 0x79,
    kVK_F1                        = 0x7A,
    kVK_LeftArrow                 = 0x7B,
    kVK_RightArrow                = 0x7C,
    kVK_DownArrow                 = 0x7D,
    kVK_UpArrow                   = 0x7E,
    kVK_Power                     = 0x7F, // Maybe Menu in different keyboard? Wtf is menu? Have to check
    // 80?
    kVK_Spotlight                 = 0x81, // Not present in keycode usage?
    kVK_Dashboard                 = 0x82, // Not present in keycode usage?
    kVK_Launchpad                 = 0x83, // Not present in keycode usage?
    // 84 ~ 8F?
    kVK_BrightnessUp              = 0x90, // Not present in keycode usage?
    kVK_BrightnessDown            = 0x91, // Not present in keycode usage?
    kVK_Eject                     = 0x92, // Not present in keycode usage?
    // 93 ~ 9F?
    kVK_ExposesAll                = 0xA0, // Not present in keycode usage?
    kVK_ExposesDesktop            = 0xA1  // Not present in keycode usage?
    // A2 ~ FF?
};
