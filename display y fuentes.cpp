#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <Windows.h>
using namespace std;

int main() {

	if (!al_init()) {
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_DISPLAY* ventana = al_create_display(800, 600);
	ALLEGRO_FONT* hello_honey = al_load_font("hello honey.otf", 70, 0);

	int ancho = GetSystemMetrics(SM_CXSCREEN);
	int alto = GetSystemMetrics(SM_CYSCREEN);

	al_set_window_title(ventana, "Mi Juego");
	al_set_window_position(ventana, ancho / 2 - 800/2, alto/2 - 600/2);

	al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);

	while (true) 
	{
		al_draw_text(hello_honey, al_map_rgb(255, 255, 255), 200, 200, NULL, "HOLA MUNDO");	
		al_flip_display();	
	}

	return 0;
}