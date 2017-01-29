#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

int export(char pwm); 
int change_duty_cycle(char pwm_number,char val_duty_cycle[]);
int change_period(char pwm_number,char val_period[]);
char check_pwm_number(char pwm[]);
int enable_disable_pwm(char pwm_number,int enable);
int unexport(char pwm_number);
void print_and_scan_option(char *);
int exit_code(void);

void sig_handler (int signo)
{
	int return_status;
	return_status=exit_code();
	if(return_status < 0)
	{
		printf("failed to clean up\n");
		exit(1);
	}
	printf("Exit the application\n");
	exit(0);
}
int main(int argc, char **argv)
{
	char pwm[16]="",val_duty_cycle[10]="",val_period[10]="";
	int return_status=0;
	char pwm_number=0;
	char get_change;
	int check_pwm=0;
	/*	set zero in buffer using memset */
	memset(pwm,0,strlen(pwm));				
	memset(val_duty_cycle,0,strlen(val_duty_cycle));
	memset(val_period,0,strlen(val_period));

	if((argc == 4 | argc == 1 )==0)
	{
		printf("Please use %s pwm0 period dutycycle or %s\n",argv[0],argv[0]);
		exit(1);
	}

	if(argc ==4)
	{									/*	user use commind line argumnet */

		pwm_number=check_pwm_number(argv[1]); 				/* 	check pwm number */
		if(pwm_number == '0' | pwm_number == '1' | pwm_number == '2' | pwm_number == '3')
			printf("pwm number=%c\n",pwm_number);
		else
		{
			printf("please give correct pwm\n");			/*	if given argument of pwm is not correct */
			exit(1);
		}
		return_status=export(pwm_number);
		if(return_status < 0)
		{
			printf("Error in export\n");
			exit(1);
		}
		else
			printf("export successfully \n");
				
		return_status = change_period(pwm_number,argv[2]);		/*	change period which is provided from user */
		if(return_status < 0)
			printf(" failed to change period \n");
		else
			printf(" pwm period is changed successfully \n");
		
		return_status = change_duty_cycle(pwm_number,argv[3]);		/*	change duty cycle which is provided from user */
		if(return_status < 0)
			printf(" failed to change duty_cycle \n");
		else
			printf(" pwm duty_cycle is change successfully \n");

		return_status=enable_disable_pwm(pwm_number,1);
		if(return_status < 0)
			printf(" failed to enable pwm \n");
		else
			printf(" pwm is enable \n");

	}
	while(1)
	{
		/*	if go for runtime decide option */
		signal(SIGINT,sig_handler);
		if(argc==1)
		{	
			printf("Please select pwmchip from below \n");
			printf("pwmchip0\npwmchip1\npwmchip2\npwmchip3\nall\n");
			scanf("%s",pwm);
			printf("selected pwm is %s \n",pwm);

			if(strstr(pwm,"pwmchip0"))      				/*	check pwm0 is present if present then export */ 
			{
				check_pwm=1;
				return_status=export('0');
			}
			if(strstr(pwm,"pwmchip1"))					/*	check pwm1 is present if present then export */
			{
				check_pwm=1;
				return_status=export('1'); 
			}
			if(strstr(pwm,"pwmchip2"))					/*	check pwm2 is present if present then export */
			{
				check_pwm=1;
				return_status=export('2');
			}
			if(strstr(pwm,"pwmchip3"))					/*	check pwm3 is present if present then export */
			{
				check_pwm=1;
				return_status=export('3');
			}
			if(strstr(pwm,"all"))					/*	if user select all then export all pwm */
			{
				check_pwm=1;
				return_status=export('A');
			}

			if(check_pwm==0)					/*	Not give a correct pwm */
			{
				printf("please give the correct pwm EX:pwm0pwm1,pwm0, all\n");
				printf("EXIT THE APPLICATION\n");
				exit(0);
			}
			check_pwm=0;

			if(return_status == 0)					/*	check export successfully or not */
				printf("export %s successfully\n",pwm);
			else
			{
				printf("export error\n");
				exit(1);
			}
			printf("Please Select PWM for changing some duty cycle period etc... \n");
			scanf("%s",pwm);

			while(1)
			{
				memset(val_duty_cycle,0,strlen(val_duty_cycle));
				memset(val_period,0,strlen(val_period));

				if(strstr(pwm,"all"))
				{				/*	if user select all then export all pwm */
					memset(pwm,0,strlen(pwm));				
					printf("Please Select PWM for changing some duty cycle period etc... \n");
					scanf("%s",pwm);
				}
				pwm_number=check_pwm_number(pwm);     			/*	check pwm_number */
				if(pwm_number == '0' | pwm_number == '1' | pwm_number == '2' | pwm_number == '3')
					printf("for changes selected pwm : %s\n",pwm);
				else
				{
					printf("please give correct pwm number\n");
					exit(1);		     			/*	if user not give valid pwm then exit the application */
				}

				print_and_scan_option(&get_change);			/* 	for print and scan user provided option function */

				if(get_change == 'D' | get_change == 'P' | get_change == 'E' | get_change =='d' | get_change == 'u'| get_change== 'p' |get_change =='e')	
					printf("you have press %c\n",get_change);
				else			
				{
					printf("please give correct option\n");	        /*	If user not give a correct input then ask again */
					while(1)
					{
						print_and_scan_option(&get_change);
						if(get_change == 'D' | get_change == 'P' | get_change == 'E' | get_change =='d' | get_change == 'u'| get_change== 'p' |get_change =='e')	
							break;
					}
				}

				switch(get_change)			
				{
					case 'D' : printf("please give the duty_cycle\n");         /*	duty cycle */
						   scanf("%s",val_duty_cycle);
						   return_status = change_duty_cycle(pwm_number,val_duty_cycle);
						   if(return_status < 0)
							   printf("failed to change pwm duty_cycle \n");
						   else
							   printf("pwm duty_cycle is change successfully \n");
						   break;

					case 'P' : printf("Please give the period\n");   	      /*	change period */
						   scanf("%s",val_period);
						   return_status = change_period(pwm_number,val_period);
						   if(return_status < 0)
							   printf("failed to change pwm period\n");
						   else
							   printf("pwm period is changed successfully \n");
						   break;


					case 'E' : return_status=enable_disable_pwm(pwm_number,1);	/*	enable pwm */
						   if(return_status < 0)
							   printf("failed to enable pwm \n");
						   else 
							   printf("Enable pwm is successfully \n");
						   break;

					case 'd' : return_status=enable_disable_pwm(pwm_number,0);	/*	disable pwm */
						   if(return_status < 0)
							   printf("failed to disable pwm\n");
						   else
							   printf("Disable pwm successfully \n");
						   break;

					case 'u' : return_status=unexport(pwm_number);
						   if(return_status < 0)
							   printf("failed to unexport pwm\n");
						   else
							   printf("unexport successfully\n");
						   break;

					case 'e' : return_status=exit_code();
						   if(return_status < 0)
						   {
							   printf("failed to clean up\n");
							   exit(1);
						   }
						   printf("Exit the application\n");
						   exit(0);
						   break;


					default : 
						   break;
				}
			}
		}

	}


}
void print_and_scan_option(char *get_change)
{
	printf("For changing dutycycle press : D\nFor changing period press : P\nFor Enable PWM  : E\nFor disable PWM : d\nFor unexport pwm : u\nFor exit this application press : e\n");
	scanf(" %c",get_change);

}

/* export pwm */
int export (char pwm)
{
	int fd=0,write_status=0;

	if(pwm == 'A')
	{
		fd=open("/sys/class/pwm/pwmchip0/export",O_WRONLY,0700);
		if(fd<0)
		{
			perror("file error");
			exit(1);
		}
		write_status=write(fd,"0",2);
		if(write_status<0)
		{
			close(fd);
			perror("export");
			return -1;
		}
		close(fd);

		fd=open("/sys/class/pwm/pwmchip1/export",O_WRONLY,0700);
		if(fd<0)
		{
			perror("file error");
			exit(1);
		}
		write_status=write(fd,"0",2);
		if(write_status<0)
		{
			close(fd);
			perror("export");
			return -1;
		}
		close(fd);

		fd=open("/sys/class/pwm/pwmchip2/export",O_WRONLY,0700);
		if(fd<0)
		{
			perror("file error");
			exit(1);
		}
		write_status=write(fd,"0",2);
		if(write_status<0)
		{
			close(fd);
			perror("export");
			return -1;
		}
		close(fd);

		fd=open("/sys/class/pwm/pwmchip3/export",O_WRONLY,0700);
		if(fd<0)
		{
			perror("file error");
			exit(1);
		}
		write_status=write(fd,"0",2);
		if(write_status<0)
		{
			close(fd);
			perror("export");
			return -1;
		}
		close(fd);
	
		return 0;
	}

	switch(pwm)
	{
	case '0' : fd=open("/sys/class/pwm/pwmchip0/export",O_WRONLY,0700);
		   break;
	case '1' : fd = open("/sys/class/pwm/pwmchip1/export",O_WRONLY,0700);
		   break;
	case '2' : fd = open("/sys/class/pwm/pwmchip2/export",O_WRONLY,0700);
		   break;
	case '3' : fd = open("/sys/class/pwm/pwmchip3/export",O_WRONLY,0700);
		   break;
	}

	if(fd<0)
	{
		perror("file error");
		exit(1);
	}

	write_status=write(fd,"0",2);

	if(write_status<0)
	{
		close(fd);
		perror("export");
		return -1;
	}
	close(fd);
	return 0;
}

int exit_code(void)
{
	int fd=0,read_status=0;
	char buf[2]="",pwm_number='e';
	int return_status=0;
	int access_var=1;

	access_var=access("/sys/class/pwm/pwmchip0/pwm0",F_OK);
	if(access_var == 0)
	{
		pwm_number='0';
		return_status=enable_disable_pwm(pwm_number,0);	/*	disable pwm */
		if(return_status < 0)
			printf("failed to disable pwm\n");
		else
			printf("Disable pwm successfully \n");


		return_status=unexport(pwm_number);
		if(return_status < 0)
			printf("failed to unexport pwm\n");
		else
			printf("unexport successfully\n");

	}
	access_var=access("/sys/class/pwm/pwmchip1/pwm0",F_OK);
	if(access_var == 0)
	{
		pwm_number='1';
		return_status=enable_disable_pwm(pwm_number,0);	/*	disable pwm */
		if(return_status < 0)
			printf("failed to disable pwm\n");
		else
			printf("Disable pwm successfully \n");


		return_status=unexport(pwm_number);
		if(return_status < 0)
			printf("failed to unexport pwm\n");
		else
			printf("unexport successfully\n");
	}
	access_var=access("/sys/class/pwm/pwmchip2/pwm0",F_OK);
	if(access_var == 0)
	{
		pwm_number='2';
		return_status=enable_disable_pwm(pwm_number,0);	/*	disable pwm */
		if(return_status < 0)
			printf("failed to disable pwm\n");
		else
			printf("Disable pwm successfully \n");


		return_status=unexport(pwm_number);
		if(return_status < 0)
			printf("failed to unexport pwm\n");
		else
			printf("unexport successfully\n");
	}

	access_var=access("/sys/class/pwm/pwmchip3/pwm0",F_OK);
	if(access_var == 0)
	{
		pwm_number='3';
		return_status=enable_disable_pwm(pwm_number,0);	/*	disable pwm */
		if(return_status < 0)
			printf("failed to disable pwm\n");
		else
			printf("Disable pwm successfully \n");


		return_status=unexport(pwm_number);
		if(return_status < 0)
			printf("failed to unexport pwm\n");
		else
			printf("unexport successfully\n");
	}
	if(pwm_number=='e')
	{
		printf("PWM is not exported\n");
		exit(1);
	}
	
}
/* check which pwm_number is selected */
char check_pwm_number(char pwm[16])
{
	if(strstr(pwm,"pwmchip0"))                                                  /*	for check pwm0		*/
		return '0';

	else if(strstr(pwm,"pwmchip1"))                                             /*	for check pwm1		*/
		return '1';

	else if(strstr(pwm,"pwmchip2"))                                             /*	for check pwm2		*/
		return '2';

	else if(strstr(pwm,"pwmchip3"))                                             /*	for check pwm3		*/
		return '3';

	return 0;
}

/* change pwm duty cycle */
int change_duty_cycle(char pwm_number,char val_duty_cycle[10])
{

	int fd=0,write_status=0;	

	switch(pwm_number)
	{
		case '0' : fd=open("/sys/class/pwm/pwmchip0/pwm0/duty_cycle",O_WRONLY,0700);	/*	change pwm0 duty cycle	*/
			   break; 
		case '1' : fd=open("/sys/class/pwm/pwmchip1/pwm0/duty_cycle",O_WRONLY,0700);	/*	change pwm1 duty cycle	*/
			   break;
		case '2' : fd=open("/sys/class/pwm/pwmchip2/pwm0/duty_cycle",O_WRONLY,0700);	/*	change pwm2 duty cycle 	*/
			   break;
		case '3' : fd=open("/sys/class/pwm/pwmchip3/pwm0/duty_cycle",O_WRONLY,0700);	/*	change pwm3 duty cycle	*/
			   break;

		default : 
			   break; 
	}

	if(fd<0)
	{
		perror("file open error");
		exit(1);
	}
	write_status=write(fd,val_duty_cycle,strlen(val_duty_cycle));
	if(write_status<0)
	{
		perror("DUTY CYCLE");
		close(fd);
		return -1;
	}
	return 0;
}
/* change pwm period */
int change_period(char pwm_number,char val_period[10])
{
	int fd=0,write_status=0;

	switch(pwm_number)
	{
		case'0'  : 
			fd=open("/sys/class/pwm/pwmchip0/pwm0/period",O_WRONLY,0700);		/*	change pwm0 period	*/
			break; 
		case '1' : 
			fd=open("/sys/class/pwm/pwmchip1/pwm0/period",O_WRONLY,0700);		/*	change pwm1 period	*/
			break;  

		case '2' :
			fd=open("/sys/class/pwm/pwmchip2/pwm0/period",O_WRONLY,0700);		/*	change pwm2 period	*/
			break; 

		case '3' :
			fd=open("/sys/class/pwm/pwmchip3/pwm0/period",O_WRONLY,0700);		/*	change pwm3 period	*/
			break; 

		default :
			break;
	}

	if(fd < 0)
	{
		perror("file open");
		exit(1);
	}

	write_status=write(fd,val_period,strlen(val_period));
	if(write_status<0)							/*	check write successfully or not	*/
	{
		perror("change period");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}

/* Enable and disable pwm */
int enable_disable_pwm(char pwm_number,int enable)
{
	int fd=0,write_status=0;

	switch(pwm_number)
	{
		case '0' :
			fd=open("/sys/class/pwm/pwmchip0/pwm0/enable",O_WRONLY,0700);		/*	enable/disbale pwm0	*/
			break;

		case '1' :
			fd=open("/sys/class/pwm/pwmchip1/pwm0/enable",O_WRONLY,0700);		/*	enable/disable pwm1	*/
			break;

		case '2' : 
			fd=open("/sys/class/pwm/pwmchip2/pwm0/enable",O_WRONLY,0700);		/*	enable/disable pwm2	*/
			break;
		case '3' :		
			fd=open("/sys/class/pwm/pwmchip3/pwm0/enable",O_WRONLY,0700);           /*	enable/disable pwm3	*/
			break;

		default : 
			break;
	}

	if(fd < 0)
	{
		perror("file open");
		exit(1);
	}

	if(enable)								/*	enable pwm	*/
		write_status=write(fd,"1",2);
	else									/*	diable pwm	*/
		write_status=write(fd,"0",2);

	if(write_status<0)
	{
		close(fd);
		perror("Enable/Disable");
		return -1;
	}
	close(fd);
	return 0;

}
/* unexport PWM */
int unexport(char pwm_number)
{
	int fd,write_status=0;

	
	switch(pwm_number)
	{
		case '0' : fd=open("/sys/class/pwm/pwmchip0/unexport",O_WRONLY,0700);
			   break;

		case '1' : fd=open("/sys/class/pwm/pwmchip1/unexport",O_WRONLY,0700);
			   break;

		case '2' : fd=open("/sys/class/pwm/pwmchip2/unexport",O_WRONLY,0700);
			   break;

		case '3' : fd=open("/sys/class/pwm/pwmchip3/unexport",O_WRONLY,0700);
			   break;

		default :
			  break;

	}

	if(fd < 0)
	{
		perror("file open");
		exit(1);
	}

	write_status=write(fd,"0",2);

	if(write_status < 0)                                                    /*	check unexport successfully or not	*/
	{
		close(fd);
		perror("unexport");
		return -1;
	}
	close(fd);
	return 0;
}
