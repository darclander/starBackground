@ Made by Darclander
@ If you want to help with any improvements or general comments you can look at 
@ https://github.com/darclander/starBackground which also contains all the source code.


NOTE BEFORE DOING ANYTHING ELSE: I do not take responsibility for any changes / things that
may happen to your computer. Feel free to look through the source code and compile it yourself
if you feel unsure. This is just a project made for fun and not meant to be taken seriously.


StarBG is a simple program for changing your desktop to a moving sky of stars. Usage is simple,
either just launch the application which will have a default of 1920 1080 300 as arguments
or;

Open a terminal -> 
	Go to the directory StarBG.exe is in ->
		Execute it with arguments ->
-w, --width: specifies the width of the window. default is 1920
-h, --height: specifies the height of the window. default is 1080
--stars: specifies the number of stars. default is 300
--video: specfies file path to a video file. (NOTE: if video is used this overrides the "star" setting).	

Example:
./starBG.exe -w 1920 -h 1080 --video ./video.mp4
./starBG.exe -w 1920 -h 1080 --stars 1000

NOTE: Be careful with the amount of stars / size of your screen because it can be quite costly.
To stop the animation just kill the application.
