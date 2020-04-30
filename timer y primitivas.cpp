#include <iostream>
#include <string>
#include <cstring>
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

	//al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);

	//eventos timer
	ALLEGRO_TIMER* segundoTimer = al_create_timer(1.0);
	ALLEGRO_TIMER* fps = al_create_timer(1.0/30);
	
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	
	al_register_event_source(event_queue, al_get_timer_event_source(fps));
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_start_timer(fps);
	al_start_timer(segundoTimer);
	
	
	int segundos = 0;
	int fotogramas = 0;
	while (true) 
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		
		if (Evento.type == ALLEGRO_EVENT_TIMER) {
			if (Evento.timer.source == segundoTimer) {
				segundos++;
			}
			else {
				fotogramas++;
				if (fotogramas % 30 == 0)
					cout << fotogramas / 30 << endl;
			}

				//cout << "no afecta";
			//
		}
		al_draw_text(hello_honey, al_map_rgb(255, 255, 255), 200, 200, NULL, ("Segundos: " + to_string(segundos)).c_str());
		
		//al_clear_to_color(al_map_rgb(segundos*10%255, 55+segundos%255, segundos*7%255));
		al_flip_display();
	}

	return 0;
}