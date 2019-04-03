#include <stdio.h>
#include <ncurses.h> // sudo apt-get install libncurses5-dev
#include <vector>
#include <string>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

#define width 30
#define height 10 

WINDOW *win_menu;

std::vector<std::string> choices = {
	"Choice 1",
	"Choice 2",
	"Choice 3",
	"Choice 4",
	"Exit",
};


void init_win(WINDOW*& win)
{
	struct winsize size;	
	if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
		throw std::runtime_error("TIOCGWINSZ error");
	
	int start_x = (size.ws_col - width);
	int start_y = (size.ws_row - height);
	if(start_x % 2)
		start_x++;
	if(start_y % 2)
		start_y++;
	start_x /= 2;
	start_y /= 2;
		
	win = newwin(height, width, start_y, start_x);
	keypad(win, TRUE);
	refresh();
}

void print_menu(WINDOW *win_menu, int highlight)
{
	
	

	int x, y, i;	

	x = 2;
	y = 2;
	box(win_menu, 0, 0);
	for(i = 0; i < choices.size(); ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(win_menu, A_REVERSE); 
			mvwprintw(win_menu, y, x, "%s", choices[i].c_str());
			wattroff(win_menu, A_REVERSE);
		}
		else
			mvwprintw(win_menu, y, x, "%s", choices[i].c_str());
		++y;
	}
	wrefresh(win_menu);
}

int main()
{	
	int highlight = 1;
	int choice = 0;
	int c;

	initscr();
	start_color();
	curs_set(0); // 0: invisible, 1: normal, 2: very visible
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
		
	init_win(win_menu);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	print_menu(win_menu, highlight);
	refresh();
	
	while(1)
	{	c = wgetch(win_menu);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = choices.size();
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == choices.size())
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(win_menu, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	//mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1].c_str());
	clrtoeol();
	refresh();
	endwin();
	return 0;
}
