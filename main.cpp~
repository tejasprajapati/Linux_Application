/* this is the main file for the execution of the programm.
it includes the main logic of the project application and as well the modules related calls are made from this file.
each module has its seperate files where the necessary functions and all variables are included.
*/

#define success 0

int modules_init(void);


int main (void)
{
	if(modules_init == success)
	log("All modules are initialized succesfully.");
	else
	{
	log("Error: problem in module initialization.");
	}

}

int modules_init(void)
{
	int status;

	if(GPIO_init()==success)
	if(SPI_init()==success)
	if(I2c_init()==success)
	if(PWM_init()==success)

	return status;
}
