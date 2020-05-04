#include <iostream>
#include <string>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <Windows.h>

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


	ALLEGRO_DISPLAY* ventana = al_create_display(800, 600);
	ALLEGRO_FONT* hello_honey = al_load_font("hello honey.otf", 70, 0);

	int ancho = GetSystemMetrics(SM_CXSCREEN);
	int alto = GetSystemMetrics(SM_CYSCREEN);

	al_set_window_title(ventana, "Mi Juego");
	al_set_window_position(ventana, ancho / 2 - 800 / 2, alto / 2 - 600 / 2);

	//al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);

	//eventos timer
	ALLEGRO_TIMER* segundoTimer = al_create_timer(1.0);
	ALLEGRO_TIMER* fps = al_create_timer(1.0 / 30);

	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(fps));
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//al_register_event_source(event_queue, al_get_mouse_event_source());

	al_start_timer(fps);
	al_start_timer(segundoTimer);


	int segundos = 0;
	int x = -1, y = -1;
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR azar = al_map_rgb(255, 50, 65);
				//rectangulo, circulo
	int botones[] = { 0,0 };

	while (true)
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);

		if (Evento.type == ALLEGRO_EVENT_TIMER) {
			if (Evento.timer.source == segundoTimer) {
				segundos++;
			}

		}
		al_clear_to_color(al_map_rgb(0, 0, 0));
		if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) 
		{
			
			x = Evento.mouse.x;
			y = Evento.mouse.y;

			if (x >= 200 && x <= 400 && y >= 280 && y <= 350) {
				botones[0] = 1;
				if(Evento.mouse.button & 1)
					cout << "x: " << x << " y: " << y << endl;
			}
			else {
				botones[0] = 0;
			}
			if (sqrt(pow(x-150,2) + pow(y-100,2)) <= 50) {
				botones[1] = 1;
				if (Evento.mouse.button & 1)
					cout << "x: " << x << " y: " << y << endl;
			}
			else {
				botones[1] = 0;
			}

			
		}
		
		//0 = false , cualquier otro numero = true
		if (botones[1]) {
			al_draw_filled_circle(150, 100, 50, blanco);
		}
		else {
			al_draw_filled_circle(150, 100, 50, azar);
		}

		if (botones[0]) {
			al_draw_filled_rectangle(200, 280, 400, 350, azar);
		}
		else {
			al_draw_filled_rectangle(200, 280, 400, 350, blanco);
		}
		
		

		al_draw_text(hello_honey, al_map_rgb(255, 255, 255), 200, 200, NULL, ("Segundos: " + to_string(segundos)).c_str());	
		//al_clear_to_color(al_map_rgb(segundos*10%255, 55+segundos%255, segundos*7%255));
		
		al_flip_display();
	}

	return 0;
}