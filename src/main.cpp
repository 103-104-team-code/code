#include "main.h" //definitions
#include "autoSelect/selection.h"
pros::Controller master(E_CONTROLLER_MASTER);
pros::ADIAnalogIn icantspellwhatisthesensorcalled ('B');
pros::ADIDigitalIn button ('C');
pros::ADIUltrasonic ultrasonic('E', 'F');
pros::ADIAnalogIn leftLineSensor('D');
pros::ADIAnalogIn rightLineSensor('H');

bool pressed = false;
// pros::Imu imu_sensor(5); // temp imu init
int count = 0;
#define ANALOG_SENSOR_PORT 'B'
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */	
void initialize()
{
	// selector::init();
 	pros::ADIAnalogIn icantspellwhatisthesensorcalled ('B');
  	icantspellwhatisthesensorcalled.calibrate();
    pros::lcd::initialize();

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */

// BRAKE MODE HOLD DOES NOT WORK IN DISABLED, VEXOS OVERRIDES
int test1 = 0;
void disabled()
{

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{

}

void autonomous()
{
	/**
	change names in autoSelect/selection.h for gui names
	selector::auton == 1 : Red Front
	selector::auton == 2 : Red Back
	selector::auton == 3 : Do Nothing
	selector::auton == -1 : Blue Front
	selector::auton == -2 : Blue Back
	selector::auton == -3 : Do Nothing
	selector::auton == 0 : Skills
	**/

	// using namespace okapi; // use okapi namespace, custom library located at projectfolder/include/okapi/api.hpp. Uncomment the #include okapi.hpp in main.h config file
	// std::shared_ptr<ChassisController> drive =
	// 	ChassisControllerBuilder()															 // chassiscontroller definition, prebuilt library. Less accurate than one with 1 or 2 tracking wheeel but we don't really have time for a good code version
	// 		.withMotors(-20, 19)															 // motor ports
	// 		.withDimensions(AbstractMotor::gearset::green, {{4_in, 12.5_in}, imev5GreenTPR}) // Green gearset, 4 in wheel diam, 12.5 in wheel track (4pi)
	// 		.build();
	// drive->setMaxVelocity(50); // set max velocity to 50 rpm (25% power on green gearset for more accurate pid)

	// if (selector::auton == 1)
	// { // run auton for Front Red
	// 	master.print(0, 0, "^ 26_in");
	// 	drive->moveDistance(26_in); // move 22 inches forward; float value
	// 	master.print(0, 0, "< 100");
	// 	drive->turnAngle(100_deg);
	// 	drive->setMaxVelocity(200);
	// 	drive->moveDistance(15_in);
	// }
	// else if (selector::auton == 2)
	// { // run auton for Back Red
	// 	master.print(0, 0, "^ 22_in");
	// 	drive->moveDistance(22_in); // move 22 inches forward; float value
	// 	master.print(0, 0, "< 100");
	// 	drive->turnAngle(90_deg);
	// }
	// else if (selector::auton == -1)
	// { // run auton for Front Blue
	// 	drive->moveDistance(26_in); // move 22 inches forward
	// 	master.print(0, 0, "> 100");
	// 	drive->turnAngle(-90_deg);
	// 	drive->setMaxVelocity(200);
	// 	master.print(0, 0, "^ 10_in");
	// 	drive -> moveDistance(10_in);
	// }
	// else if (selector::auton == -2)
	// { // run auton for Back Blue; commented out because throws error if else block is empty
	// 	master.print(0, 0, "^ 10_in");
	// 	drive->moveDistance(22_in); // move 22 inches forward
	// 	master.print(0, 0, "> 100");
	// 	drive->turnAngle(-90_deg);
	// }
}//test
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().t
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol()
{						  // driver control period
	while(true) {
		pros::lcd::print(0, "Potentiomiter position: %d\n", icantspellwhatisthesensorcalled.get_value());
		pros::lcd::print(2, "Ultrasonic position: %d\n", ultrasonic.get_value());
		pros::lcd::print(3, "Ultrasonic position: %d\n", leftLineSensor.get_value());
		pros::delay(20);
		if (button.get_value() == 1) {
			pros::lcd::print(1, "Button is pressed: %d\n", button.get_value());
		}
		else {
			pros::lcd::print(1, "Button is not pressed");
		}
		if (leftLineSensor.get_value() < 2000) {
			pros::lcd::print(3, "Ultrasonic position: %d\n", leftLineSensor.get_value());
			master.rumble("-");
		}
		if (rightLineSensor.get_value() < 2000) {
			pros::lcd::print(4, "Ultrasonic position: %d\n", rightLineSensor.get_value());
			master.rumble("-");
		}
	}
}

