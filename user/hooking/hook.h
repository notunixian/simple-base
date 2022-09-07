#ifndef HOOK_H
#define HOOK_H

// functions inside of hook.cpp
void perform_hooks();


// all hooks will go here.
void on_player_join(app::u00CCu00CDu00CDu00CCu00CEu00CFu00CCu00CCu00CCu00CFu00CEu00CFu00CFu00CDu00CEu00CEu00CEu00CDu00CFu00CCu00CFu00CFu00CD * class_ptr, app::u00CDu00CFu00CDu00CEu00CDu00CDu00CFu00CCu00CDu00CFu00CCu00CCu00CDu00CCu00CCu00CEu00CFu00CCu00CCu00CFu00CDu00CEu00CF * player_ptr, MethodInfo * method);
void on_player_leave(app::u00CCu00CDu00CDu00CCu00CEu00CFu00CCu00CCu00CCu00CFu00CEu00CFu00CFu00CDu00CEu00CEu00CEu00CDu00CFu00CCu00CFu00CFu00CD * class_ptr, app::u00CDu00CFu00CDu00CEu00CDu00CDu00CFu00CCu00CDu00CFu00CCu00CCu00CDu00CCu00CCu00CEu00CFu00CCu00CCu00CFu00CDu00CEu00CF * player_ptr, MethodInfo * method);
void update(app::InputManager * __this, app::InputUpdateType__Enum updateType, app::InputEventBuffer * eventBuffer, MethodInfo * method);

#endif