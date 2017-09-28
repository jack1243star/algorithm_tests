; ^!z::  ; Control+Alt+Z hotkey.

^c::  ; Control+Z hotkey.

MouseGetPos, MouseX, MouseY
PixelGetColor, color, %MouseX%, %MouseY%
intensity := Mod(color, 256)
clipboard := Format("{1:4d}", intensity)
return