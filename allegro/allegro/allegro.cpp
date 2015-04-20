#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <iostream>

int main()
{
	ALLEGRO_DISPLAY *display;

	if (al_init())
		al_show_native_message_box(NULL, NULL, NULL, "Could not do it allegro 5", NULL, NULL);

	display = al_create_display(800, 600);

	if (!display)
		al_show_native_message_box(display, "Sample Title", "Display Settings", "Display window was not created seccesfully", NULL, NULL);

	al_show_native_message_box(display, "MessageBox Title", "Error", "Disply not able to show", NULL, NULL);

	al_destroy_display(display);

	return 0;
}