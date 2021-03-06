
#include <iostream>
#include <stdio.h>
#include <conio.h>

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "win_setup.h"

#include <chrono>
#include <thread>
#include "types.h"
#include "generate.h"
#include "draw.h"
#include "step.h"

Node *nodes; //Nodes array
int width, height; //Maze dimensions

//CHAR_INFO* consoleBuffer = 0;
//HANDLE wHnd; /* write (output) handle */
//HANDLE rHnd; /* read (input handle */
///* A COORD struct for specificying the console's screen buffer dimensions */
//COORD bufferSize;
///* Setting up different variables for passing to WriteConsoleOutput */
//COORD characterBufferSize;
//COORD characterPosition = { 0, 0 };
//SMALL_RECT consoleWriteArea;

//enum map_cell
//{
//	space = 0,
//	stena = 1,
//	person = 2,
//	zvezda = 3,
//	move_left = 75,
//	move_right = 77,
//	move_down = 80,
//	move_up = 72
//};

int init()
{
	int i, j;
	Node *n;

	//Allocate memory for maze
	nodes = (Node*)calloc(width * height, sizeof(Node));
	if (nodes == NULL) return 1;

	//Setup crucial nodes
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			n = nodes + i + j * width;
			if (i * j % 2)
			{
				n->x = i;
				n->y = j;
				n->dirs = 15; //Assume that all directions can be explored (4 youngest bits set)
				n->c = ' ';
			}
			else n->c = '#'; //Add walls between nodes
		}
	}
	return 0;
}








//void gen_level(int h, int w, int* field) {
//	main_generate(field);
//	create_room2(map_h, map_w, field);
//	zvezda_random(map_h, map_w, field);
//	mob_random(map_h, map_w, field, col_mob2, cord_mob);
//	sword_random(map_h, map_w, field);
//
//
//	fill_field(map_h, map_w, field);
//
//	draw_field(map_h, map_w, field);
//	draw_menu(menu_h, menu_w, person_state, map_h);
//}
//bool proverka_zvezd(int h, int w, int* field) 
//{
//	bool o = false;
//	for (int i = 0; i < h; i++)
//	{
//		for (int j = 0; j < w; j++) 
//		{
//			int c = field[w*i + j];
//			if (c == zvezda) 
//			{
//				o = true;
//				return o;
//
//			}
//		}
//	}
//}


int main()
{


	display_t display_settings;

	 display_settings.consoleBuffer = 0;
	 display_settings.wHnd; /* write (output) handle */
	 display_settings.rHnd; /* read (input handle */
	     /* A COORD struct for specificying the console's screen buffer dimensions */
	 display_settings.bufferSize;
	/* Setting up different variables for passing to WriteConsoleOutput */
	 display_settings.characterBufferSize;
	 display_settings.characterPosition = { 0, 0 };
	 display_settings.consoleWriteArea;


	person_status_t person_state;
	person_state.col_hearts = 3;
	person_state.col_sw = 0;
	person_state.mood = mood_normal;
	person_state.col_zv = 0;
	
	map_t map;
	map.h = 25;
	map.w = 25;
	//short int map_h = 25, map_w = 25;
	short int menu_h = 6;
	short int menu_w = map.w;
	short int win_h = map.h +menu_h, win_w = map.w;
	 map.field = new int[map.h *map.w];
	height = map.h;
	width = map.w;
	init();

	{

		setup_window(win_h, win_w, display_settings);

		

	}
	
	const int max_cout=18;
	cord_t cord_mob[max_cout];
	int col_mob2=0;
	int mood_e = 0;

	int color[2];
	
	level_gener( map, col_mob2, mood_e, cord_mob, person_state, width, height, nodes);
	
	//main_generate(field);
	//create_room2(map_h, map_w, field);
	//zvezda_random(map_h, map_w, field);
	//mob_random(map_h, map_w, field,col_mob2,cord_mob);
	//sword_random(map_h, map_w, field);
	//

	//fill_field(map_h, map_w, field);
	//
	//draw_field(map_h, map_w, field);
	//draw_menu(menu_h, menu_w, person_state, map_h);
	generaty_colors(map, color);
	draw_field(map,color, display_settings);
	draw_menu(menu_h, menu_w, map, person_state, display_settings);
	//ошибка возможна в этом месте
	int max_zv = 20;
	int n = 7475474;
	int st;//шаг
	int mood_2 = 0;
	int res= 0;
	int mood_stop = 5;//кол-во шагов, после которого хорошее настроение перейдет в нормальное
	bool proverka;
	move_obj_desc_t der;
	int start_x = 5;
	int start_y = 4;
	der.from_y = start_y;
	der.from_x = start_x;
	der.name = person;
	move_res_t f;

	/////////////////////

	for (/*int i = 0; i < n;i++*/;;)
	{
		
		res = 0;

		if (_kbhit())
			res = _getch();
		else
		{
			res = 0;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		//system("cls");
		switch (res)
		{
		case move_down:
			der.to_x = der.from_x;
			der.to_y = der.from_y + 1;
			break;
		case move_up:
			der.to_x = der.from_x;
			der.to_y = der.from_y - 1;
			break;
		case move_left:
			der.to_x = der.from_x - 1;
			der.to_y = der.from_y;
			break;
		case move_right:
			der.to_x = der.from_x + 1;
			der.to_y = der.from_y;
			break;
		default:
			der.to_y = der.from_y;
			der.to_x = der.from_x;
			break;


		}

		//std::cout << "res " << res << std::endl;
	/*	step_in_labyrinth(h, w, field, res);*/
		f = move_step_in_labyrinth(map, der);
		int v = 0;
		for (int i = 0; i < 625; i++) {
			if (map.field[i] == person) {
				v++;
			}
		}
		int k;
		k = v;
		
		if (f.ok == true)
		{

			if (f.name == mob) {

				for (int i = 0; i < col_mob2; i++) {

					if (der.to_x == cord_mob[i].x && der.to_y == cord_mob[i].y) {

						for (int b = i; b < col_mob2 - 1; b++)
						{
							cord_mob[b].x = cord_mob[b + 1].x;
							cord_mob[b].y = cord_mob[b + 1].y;
						}
						col_mob2--;
						break;
					}

				}
			}
			if (person_state.mood == mood_good && mood_e < mood_stop)
			{
				printf("\7");

				mood_e++;
			}
			else if (person_state.mood == mood_good && mood_e >= mood_stop)
			{
				person_state.mood = mood_normal;
				mood_e = 0;
				mood_2 = 0;
			}
			if (person_state.mood == mood_normal)
			{
				mood_2++;
				if (mood_2 >= 30)
				{
					person_state.mood = mood_bad;
					printf("\7");
				}
			}



			der.from_x = der.to_x;
			der.from_y = der.to_y;


			if (f.name == zvezda)
			{
				person_state.mood = mood_good;
				person_state.col_zv = person_state.col_zv + 3;
				printf("\7");
				if (person_state.col_zv == max_zv) {


					for (int po = 0; po < 5000; po++)
					{
						/*printf("The end");*/
						std::cout << "      The end" << std::endl;
						printf("\7");
					}
					return 0;
				}
			}
			if (f.name == sword)
			{
				person_state.mood = mood_good;
				person_state.col_sw++;
			}
			if (f.name == mob)
			{

				if (person_state.col_sw == 0 && person_state.mood == mood_good)
				{
					//викторина
					for (int po = 0; po < 5000; po++)
					{
						printf("\7");
					}
					return 0;

				}
				else if (person_state.col_sw > 0) {
					person_state.mood = mood_bad;
					person_state.col_sw--;
				}
				else if (person_state.col_sw == 0)
				{
					person_state.mood = mood_bad;
					person_state.col_hearts--;
					if (person_state.col_hearts == 0)
					{
						for (int po = 0; po < 50000; po++)
						{
							std::cout << "      The end" << std::endl;
							printf("\7");
						}
						return 0;
					}
				}
				else
				{
					//убил монстра
				}
			}

		}
		else
		{

		}

		/*if (i == n)
		{
		std::cout << "The steps ended";

		}*/
		mob_walking(map, cord_mob, col_mob2);
		{
			int v = 0;
			for (int i = 0; i < 625; i++) {
				if (map.field[i] == person) {
					v++;
				}
			}
			int k;
			k = v;
			
		}
		
		draw_field( map, color, display_settings);
		{
			int v = 0;
			for (int i = 0; i < 625; i++) {
				if (map.field[i] == person) {
					v++;
				}
			}
			int k;
			k = v;
			
		}
		draw_menu(menu_h, menu_w, map, person_state, display_settings);
		
		if (f.name == exittt) {
			f.name = stena;
			generaty_colors(map, color);
			level_gener( map, col_mob2, mood_e, cord_mob, person_state, width, height, nodes);
			der.from_y = start_y;
			der.from_x = start_x;
			int v = 0;
			for (int i = 0; i < 625; i++) {
				if (map.field[i] == person) {
					v++;
				}
			}
			int k;
			k = v;
		}

	
	}
		

	/*step_in_labyrinth(h, w, field,res);*/
	//system("pause");
	return 0;
}


