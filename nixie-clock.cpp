
// Nixie tube clock live wallpaper
// © Pikku-a 2023-2024

#include <iostream>
#include <ctime>		// For getting time
//#include <windows.h>		// For changing wallpaper
#include <stdlib.h>		// For linux cmd to use a cmd command to change wallpaper
#include <Magick++.h>		// For editing the image		//"C:\Program Files\ImageMagick-7.1.0-Q16-HDRI\include\Magick++.h" ?
#include <string>
#include <chrono>		// This and the one below are for sleep_for milliseconds
#include <thread>
#include <unistd.h>		// This
#include <linux/limits.h>	// and this are for getting the path to the program directory

using namespace Magick;
using namespace std;

int get_digit_count(int number);

string get_selfpath() {
    char buff[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
    if (len != -1) {
		buff[len] = '\0';
		return string(buff);
    }else{
		return "Failed to get path";
	}
}
		
int main(/*int argc,char **argv*/) { //arguments are for imagemagick, only necessary for windows
	
	// Check that libraries needed for imagemagick++ are installed and if not, install them
	//

	// Initialize imagemagick (only necessary for windows)
	//InitializeMagick(*argv); //C:\Program Files\ImageMagick-7.1.0-Q16-HDRI\ 
	
	Magick::InitializeMagick(nullptr);
	
	// Get path to program directory and add "/pics/final.png" to it
	string selfpath = get_selfpath();
	string::size_type t = selfpath.find_last_of("/");
	selfpath = selfpath.substr(0,t);
	string selfpathFolder = selfpath;
	selfpath = selfpath+"/pics/final.png";
	cout << "Path to program and final.png: " << selfpath << "\n";
	
	while(true) {
		
		// Check here if wallpaper is visible or if there is no active window and only execute code if it's true? (couldn't find a way to do this in linux (at least not in wayland))
		
		// GET TIME - Move this to a different script?
		time_t currentTime;
		struct tm *localTime;

		time(&currentTime);                   // Get the current time
		localTime = localtime(&currentTime);  // Convert the current time to the local time

		int hour = localTime->tm_hour;
		int min = localTime->tm_min;
		int sec = localTime->tm_sec;

		cout << "Current time is : " << hour << ":" << min << ":" << sec << "\n";
		
		
		// CREATE WALLPAPER IMAGE
		
		// Another option would be to use batch or bash - with gimp for example (the AI assistant project could use it for converting files to other formats for example (e.g.: https://www.gimp.org/tutorials/AutomatedJpgToXcf/))
		//system("mybatchfile.bat"); or system("mybashfile.sh"); for linux
		// If someone else than me is reading this, just ignore these comments.
		
		// Construct the image object
		Image image;
		Image clocknum;
		
		try {
			
			// Read a file into image object
			image.read(selfpathFolder+"/pics/bg.png");		// Background image (originally bg.png was used, but I changed it so the period.png:s don't need to be added every time. EDIT: Changed it back for now.)
			clocknum.read(selfpathFolder+"/pics/blank.png");	// Nixie tube (clock number)
			
			// Variables
			int x = 290; 		//image x position (410 originally)
			int y = 420; 		//image y position (360 originally)
			string imgnums[8] = {"blank","blank","period","blank","blank","period","blank","blank"};
			
			// Convert numbers to string and add them to the array
			// Hours
			string s = to_string(hour);
			for (int i=0; i<s.size(); i++) {
				if (get_digit_count(hour) == 1) {
					imgnums[i] = "blank"; //First num
					imgnums[i+1] = s[i]; //Second num
				}else{
					imgnums[i] = s[i];
				}
				//cout << s[i] << "\n";
			}
			// Minutes
			s = to_string(min);
			for (int i=0;i<s.size();i++) {
				if (get_digit_count(min) == 1) {
					imgnums[i+3] = "blank";
					imgnums[i+4] = s[i];
				}else{
					imgnums[i+3] = s[i];
				}
				//cout << s[i] << "\n";
			}
			// Seconds
			s = to_string(sec);
			for (int i=0;i<s.size();i++) {
				if (get_digit_count(sec) == 1) {
					imgnums[i+6] = "blank";
					imgnums[i+7] = s[i]; // In seconds when it's 0 it draws it to the wrong position for some reason (does the same happen to minutes and hours?)
				}else{
					imgnums[i+6] = s[i];
				}
				//cout << s[i] << "\n";
			}
			
			// Paste the number images to the background image
			for (int i=0;i<8;i++) {
				x+=140;
				//if (i != 2 && i != 5) { //Don't draw the period.png images to the background so less stuff needs to be drawn every second (do this only if using final.png as base image)
					clocknum.read(selfpathFolder+"/pics/"+imgnums[i]+".png");
					image.composite(clocknum,x,y,OverCompositeOp);
					//cout << "Composite image " << imgnums[i] << "\n";
				//}
			}
			
			// Write the image to a file
			image.write(selfpathFolder+"/pics/final.png"); // "/usr/share/backgrounds/final.png"
			
		}
		catch(Exception &error_) {
			cout << "Caught exception: " << error_.what() << "\n";
			return 1;
		}
		
		
		// SET WALLPAPER
		
		/*/In windows
		const wchar_t *path = L"pics\final.png";
		int result;
		result = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void *)path, SPIF_UPDATEINIFILE);
		//int result = SystemParametersInfo( SPI_SETDESKWALLPAPER, 0, L"pics\final.png", SPIF_SENDCHANGE); //Would this alone work?
		if (result==true) {
			cout << "Changed wallpaper successfully" << "\n";
		}else{
			cout << "Could not change wallpaper" << "\n";
		}*/
		
		// Gnome - NOTE: Currently it changes it only on light theme - Make it use the current theme or something.
  		int ret = system(("gsettings set org.gnome.desktop.background picture-uri file://"+selfpath).c_str());
                //system(("gsettings set org.gnome.desktop.background picture-uri "+selfpath).c_str()); // 'pics/final.png' //'file:////usr/share/backgrounds/final.png'		
                if (ret == -1) {
		    cout << "Failed to set wallpaper" << "\n";
		}else{
		    cout << "Wallpaper set" << "\n";
		}
		/*/ Cinnamon - In this version there is flickering. Not sure if there is anything I can do to fix that.
		int ret = system(("gsettings set org.cinnamon.desktop.background picture-uri file://"+selfpath).c_str());
		if (ret == -1) {
	          cout << "Failed to set wallpaper" << "\n";
		  //cout << "The command used: " << "gsettings set org.cinnamon.desktop.background picture-uri file://" << selfpath.c_str();
		}else{
		  cout << "Wallpaper set" << "\n";
		  //cout << ret << "\n";
		}*/

		// Execute everything only every 800 milliseconds for better performance
		this_thread::sleep_for(chrono::milliseconds(800)); //Maybe make the number a little lower so it doesn't skip seconds (sometimes rarely)
		// Also use a variable so it's easier to change?
		
	}
	return 0;
}


// Get amount of digits in number function
int get_digit_count(int number) {
   int count = 0;
   while(number != 0) {
	  number = number / 10;
	  count++;
   }
   return count;
}

// It seems that sometimes the background has to be changed manuall first before this works
// Like on cmd: gsettings set org.gnome.desktop.background picture-uri 'path/to/final.png'

// The program can be stopped from terminal with "pkill nixie-clock" - Maybe add some easier way to do it (for example a keyboard shortcut)

/*
g++ -o nixie-clock nixie-clock.cpp `Magick++-config --cxxflags --cppflags --ldflags --libs`
graphicsmagick-libmagick-dev-compat package is needed to compile it. (And run it?)
*/
