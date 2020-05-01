#include <iostream>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
#include <Windows.h>
#include <allegro5/allegro_image.h>
using namespace std;

int main() {

	if (!al_init()) {
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_init_image_addon();
	ALLEGRO_DISPLAY* ventana = al_create_display(800, 600);
	ALLEGRO_FONT* hello_honey = al_load_font("hello honey.otf", 70, 0);

	int ancho = GetSystemMetrics(SM_CXSCREEN);
	int alto = GetSystemMetrics(SM_CYSCREEN);

	al_set_window_title(ventana, "Mi Juego");
	al_set_window_position(ventana, ancho / 2 - 800 / 2, alto / 2 - 600 / 2);

	ALLEGRO_TIMER* segundoTimer = al_create_timer(1.0);
	ALLEGRO_TIMER* FPS = al_create_timer(1.0/30);
	ALLEGRO_EVENT evento;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	al_register_event_source(queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(queue, al_get_timer_event_source(FPS));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_start_timer(segundoTimer);
	al_start_timer(FPS);
	
	//Cursor
	ALLEGRO_BITMAP *a = al_load_bitmap("default.png");
	ALLEGRO_MOUSE_CURSOR* cursorDefault = al_create_mouse_cursor(a, 0, 0);
	al_set_mouse_cursor(ventana, cursorDefault);
	//al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
	int segundo = 0;
	int countFPS = 0;
	int x, y = x = 0;
	while (true)
	{
		al_wait_for_event(queue, &evento);
		if (evento.type == ALLEGRO_EVENT_TIMER) {
			if (evento.timer.source == segundoTimer) {
				segundo++;
			}
			if (evento.timer.source == FPS) {
				countFPS++;
				if (countFPS % 30 == 0)
					cout << countFPS << endl;
			}

		}
		if (evento.type == ALLEGRO_EVENT_MOUSE_AXES) 
		{
			y = evento.mouse.y;
			x = evento.mouse.x;

			cout << "x: " << x << " y: " << y << endl;

			if (sqrt(pow(x - 300, 2) + pow(y - 300, 2)) <= 26)
				cout << "Estupida mi pelo idiota xd \n";
		}
		
		//al_clear_to_color(al_map_rgb(segundo * 10 % 255, segundo * 3 % 255, segundo * 7 % 255));
		
		al_clear_to_color(al_map_rgb(0, 0, 0));
		
		al_draw_text(hello_honey, al_map_rgb(255, 255, 255), 200, 200, NULL, ("Segundo: " + to_string(segundo)).c_str());
		//al_draw_filled_rectangle(300, 300, 400, 400, blanco);
		//al_draw_line(2, 1, 6, 1, blanco, 2);
		al_draw_filled_circle(300, 300, 25, blanco);
		al_flip_display();
	}

	return 0;
}