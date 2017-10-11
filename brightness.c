/*
 * brightness.c
 *
 * Author:   Michael K Schumacher (github: mkschu)
 * Created:  08-Oct-2017
 * Modified: 11-Oct-2017
 *
 * This program creates a command-line utility to manage display
 * brightness on laptops running an Intel CPU and PCI bridge. With
 * Intel CPU/bridge and AMD Radeon graphics, adjusting the brightness
 * does not work via the normal methods, so it will have to be done
 * by explicitly modifying the contents of the brightness file in
 * the /sys/class/backlight entry.
 *
 * Although the resulting binary can be run from any location (e.g.
 * in your Home directory), the easiest method is to run install
 * from the accompanying Makefile, which will copy the binary into
 * /usr/local/bin, allowing it to be called directly from the PATH
 */

/*############################################.
 *          LICENSE INFO                      *
 *                                            *
 * This work is released under the GNU GPLv2. *
 * See the LICENSE file in the application    *
 * parent directory for more information.     *
 *############################################*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Preprocess string to brightness path
#define DIR_PATH "/sys/class/backlight/intel_backlight/brightness"


/*
 * procedure curr_brightness ()
 *
 * Parameters: none
 * Returns: int
 *
 * This function will use cat to look up the current screen
 * brightness from the DIR_PATH, and return it as an integer
 */
int curr_brightness ()
{
  char command[1024];
  char buffer[1024];
  char result[1024];
  FILE *fp;
  int brightness;

  // Create system call to cat the brightness file
  sprintf (command, "/bin/cat %s", DIR_PATH);

  // Open pipe FILE pointer with system call
  fp = popen (command, "r");

  // Check whether pipe is null
  if (fp != NULL)
  {
    // Use fgets to retrieve value from pipe
    while (fgets (result, 1023, fp) != NULL)
    {
      // Print the pipe value to buffer
      sprintf (buffer, "%s", result);
    }
  }
  else
  {
    // Print error and exit if pipe is null
    printf ("ERROR: Could not find brightness");
    exit (1);
  }

  // Close FILE pipe
  pclose (fp);

  // Convert buffer to INT
  brightness = atoi (buffer);

  // Return integer value
  return brightness;
}


/*
 * procedure set_brightness ()
 *
 * Parameters: char pointer new_brightness
 * Returns: void
 *
 * This function will take an argument and use it to overwrite the
 * DIR_PATH file, thereby manually changing the display brightness
 */
void set_brightness (char *new_brightness)
{
  char command[1024];
  FILE *fp;

  // Use 'echo >' to overwrite DIR_PATH file with user argument
  sprintf (command, "/bin/echo %s > %s", new_brightness, DIR_PATH);

  // Open FILE pointer pipe and call command
  fp = popen (command, "r");

  // Close the pipe
  pclose (fp);
}


/*
 * procedure inc_brightness
 *
 * Parameters: INT curr_brightness,
 *             INT step
 * Returns: void
 * 
 * This function takes two arguments -- the current brightness and
 * the amount user wishes to increase by -- and adds them together
 * to get a new brightness value. It then uses this value to
 * overwrite the brightness file, thus changing the display
 * brightness.
 */
void inc_brightness (int curr_brightness,
		     int step)
{
  int new_brightness;
  char command[1024];
  FILE *fp;

  // Add current to desired increase to get new value
  new_brightness = curr_brightness + step;

  // Create system command to 'echo >' overwrite the brightness file
  sprintf (command, "/bin/echo %d > %s", new_brightness, DIR_PATH);

  // Create FILE pointer pipe to execute the system command
  fp = popen (command, "r");

  // Close the FILE pipe
  pclose (fp);
}


/*
 * procedure dec_brightness ()
 *
 * Parameters: INT curr_brightness,
 *             INT step
 * Returns: void
 *
 * This function behaves exactly like inc_brightness() above,
 * except that it decreases the user's step input from the
 * current brightness, thus decreasing the value written to the
 * brightness file
 */
void dec_brightness (int curr_brightness,
		     int step)
{
  int new_brightness;
  char command[1024];
  FILE *fp;

  // Subtract step from current brightness to get new value
  new_brightness = curr_brightness - step;

  // Create command using 'echo >' to overwrite brightness file
  sprintf (command, "/bin/echo %d > %s", new_brightness, DIR_PATH);

  // Open FILE pointer pipe to execute system call
  fp = popen (command, "r");

  // Close FILE pipe
  pclose (fp);
}


int main (int argc,
	  char **argv)
{
  char *command;
  char *argument;

  // If there are no CLI-args provided, assume user just wants
  // to show current brightness
  if (argc == 1)
  {
    command = "show";
  }
  // If there is at least one CLI arg provided, accept it as
  // the command (show, set, inc, or dec)
  if (argc >= 2)
  {
    command = argv[1];
  }
  // If there is a second CLI arg provided, accept it as the
  // parameter (value to SET at, or amount by which to INC or DEC)
  if (argc == 3)
  {
    argument = argv[2];
  }
      

  // If the command is to show, execute the curr_brightness()
  // procedure and print the value
  if (strcmp (command, "show") == 0)
  {
    printf ("Current brightness: %d\n", curr_brightness ());
  }

  // If the command is to set, execute the set_brightness()
  // procedure with CLI-argument as the parameter
  else if (strcmp (command, "set") == 0)
  {
    set_brightness (argument);
    printf ("New brightness: %d\n", curr_brightness ());
  }

  // If the command is to increase or decrease, call the
  // appropriate procedure with the CLI argument
  else if (strcmp (command, "inc") == 0)
  {
    inc_brightness (curr_brightness (),
                    atoi (argument));
    printf ("New brightness: %d\n", curr_brightness ());
  }
  else if (strcmp (command, "dec") == 0)
  {
    dec_brightness (curr_brightness (),
                    atoi (argument));
    printf ("New brightness: %d\n", curr_brightness ());
  }

  // If the command is not one of the available options,
  // print an error message and exit
  else
  {
    printf ("ERROR: Not an available procedure.\n");
    printf ("Permitted commands: show, set, inc, dec.\n");
    exit (1);
  }

  return 0;
}
