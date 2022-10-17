#ifndef HOOK_H
#define HOOK_H

// functions inside of hook.cpp
void perform_hooks();


// all hooks will go here.
void on_player_join(app::u00CEu00CCu00CEu00CEu00CCu00CCu00CDu00CCu00CFu00CDu00CEu00CEu00CDu00CEu00CFu00CFu00CCu00CFu00CEu00CCu00CEu00CCu00CD * class_ptr, app::u00CEu00CFu00CEu00CDu00CEu00CEu00CCu00CDu00CDu00CFu00CDu00CFu00CEu00CEu00CDu00CDu00CEu00CFu00CCu00CFu00CFu00CCu00CE * player_ptr, MethodInfo * method);
void on_player_leave(app::u00CEu00CCu00CEu00CEu00CCu00CCu00CDu00CCu00CFu00CDu00CEu00CEu00CDu00CEu00CFu00CFu00CCu00CFu00CEu00CCu00CEu00CCu00CD * class_ptr, app::u00CEu00CFu00CEu00CDu00CEu00CEu00CCu00CDu00CDu00CFu00CDu00CFu00CEu00CEu00CDu00CDu00CEu00CFu00CCu00CFu00CFu00CCu00CE * player_ptr, MethodInfo * method);
void update(app::InputManager * __this, app::InputUpdateType__Enum updateType, app::InputEventBuffer * eventBuffer, MethodInfo * method);



#endif