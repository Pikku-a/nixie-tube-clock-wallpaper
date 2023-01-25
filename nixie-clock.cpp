#include <iostream>
#include <ctime>		//For getting time
#include <windows.h>	//For changing wallpaper
//#include <stdlib.h>	//For linux cmd to use a cmd command to change wallpaper
#include "C:\Program Files\ImageMagick-7.1.0-Q16-HDRI\include\Magick++.h" //<Magick++.h>	//For editing the image
//Ok... Tuolla se tunnistaa sen. Mutta imagemagick kansioissa ne header tiedostojen polut vaikuttaa olevan väärin laitetut. Jos niitä alkaa muuttaa, ongelma katoaa ja siirtyy seuraavaan. Mutta niitä on niin paljon, että turha aloittaa sellaista.
//#include <chrono>		//Not necessary probably

//using namespace Magick;
using namespace std;

int main(int /*argc*/,char **argv) { //arguments are for imagemagick, not sure if necessary
	
	//Initialize imagemagick (not sure if necessary)
	InitializeMagick('C:\Program Files\ImageMagick-7.1.0-Q16-HDRI'); //*argv //C:\Program Files\ImageMagick-7.1.0-Q16-HDRI\include
	
	//GET TIME - Move this to a different script?
	time_t currentTime;
	struct tm *localTime;

	time(&currentTime);                   // Get the current time
	localTime = localtime(&currentTime);  // Convert the current time to the local time

	int hour = localTime->tm_hour;
	int min = localTime->tm_min;
	int sec = localTime->tm_sec;

	cout << "Current time is : " << hour << ":" << min << ":" << sec << "\n";
	
	/*time_t t = time(0); //Get time
	time_t t2 = chrono::system_clock::to_time_t(chrono::system_clock::now());
	t3 = now.time_of_day().hours;
	cout << "Time 1: " << ctime(&t) << "\n";
	cout << "Time 2: " << ctime(&t2) << "\n";
	cout << "Time 3: " << t3 << "\n";*/
	
	
	//CREATE WALLPAPER IMAGE
	
	//Another option would be to use batch or bash - with gimp for example (the AI could use it for converting files to other formats for example (e.g.: https://www.gimp.org/tutorials/AutomatedJpgToXcf/))
	//system("mybatchfile.bat"); or system("mybashfile.sh"); for linux
	
	//Construct the image object
	Image image;
	
	try {
		//Read a file into image object
		image.read("pics/bg.png");
		
		//Do things
		
		//Vars
		int x = 410; //xoffset?
		int y = 360; //yoffset?
		int imgNum = 0; //image number
		
		//Testing
		image.composite("blank.png",x,y,OverCompositeOp);
		
		/*if (get_digit_count(hour)) == 1) { //If there is only one digit in the hours?
            //image.composite(image_to_overlay, xoffset, yoffset, OverCompositeOp)?
			//https://imagemagick.org/Magick++/tutorial/Magick++_tutorial.pdf#page=21
			//https://imagemagick.org/script/composite.php
			//https://superuser.com/questions/1581256/how-to-overlay-two-images-with-position-and-scale-in-imagemagick
			image.composite("blank.png",x,y,OverCompositeOp); //somehow add blank.png image to the big image - also specify the location
		}
        for (imgNum=0;i<2;i++) {
            image.append(v); //?
		}
        image.append("period.png")
		
		if (get_digit_count(min)) == 1) {
            //pics.append("blank.png");
		}
        for v in str(start.minute):
            //pics.append(v)
        //pics.append("period.png")
		
		if (get_digit_count(sec)) == 1) {
            //pics.append("blank.png");
		}
        for v in str(start.second):
            pics.append(v)
		*/
		
		//Write the image to a file
		image.write("final.png");
		
	}
	catch(Exception %error_) {
		cout << "Caught exception: " << error_.what() << "\n";
		return 1;
	}
	
	
	//SET WALLPAPER
	
	//In windows
    const wchar_t *path = L"pics\final.png";
    int result;
    result = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void *)path, SPIF_UPDATEINIFILE);
	//int result = SystemParametersInfo( SPI_SETDESKWALLPAPER, 0, L"pics\final.png", SPIF_SENDCHANGE); //Would this alone work?
    if (result==true) {
		cout << "Changed wallpaper successfully" << "\n";
	}else{
		cout << "Could not change wallpaper" << "\n";
	}
	
	//In gnome (linux) (change the file location)
	//system(gsettings set org.gnome.desktop.background picture-uri file:////usr/share/backgrounds/ubuntu-default-greyscale-wallpaper.png)
	
	
	return 0;
	
}

//get_digit_amount script
int get_digit_count(int number) {
   int count = 0;
   while(number != 0) {
	  number = number / 10;
	  count++;
   }
   return count;
}