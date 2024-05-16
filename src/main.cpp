#include "main.h"
#include "autoSelect/selection.h"
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "arch user btw");

	pros::lcd::register_btn1_cb(on_center_button);
	selector::init(); // initialize selector
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

 void lauto() {
 }

 void rauto() {
 }

  void cross() {
	// baseline cross

	pros::Motor fleft_mtr(11);
	pros::Motor bleft_mtr(20);
	pros::Motor_Group left_mtr({fleft_mtr, bleft_mtr});
	
	pros::Motor fright_mtr(1);
	pros::Motor bright_mtr(6);
	pros::Motor_Group right_mtr({fright_mtr, bright_mtr});
	right_mtr.set_reversed(true);

	pros:Motor arm_mtr(9);

	// fwd
	right_mtr.move_velocity(100);
	left_mtr.move_velocity(100);
	pros::delay(2200);

	// stop
	right_mtr.move_velocity(0);
	left_mtr.move_velocity(0);
 }

void autonomous() {
	using namespace okapi;
	if(selector::auton == 1){ //run auton for Front red on gui
		lauto();
	}
	else if(selector::auton == 2){ //Red back
		rauto();
	}
	else if(selector::auton == 3){ // Do nothing
		cross();
	}
	else if(selector::auton == -1){ // Blue front
		return;
	}
	else if(selector::auton == -2){ // Blue back
		return;
	}
	else if(selector::auton == -3){ // Do nothing - blue gui
		return;
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
struct motorPower {
	double leftmotor;
	double rightmotor;
};

 motorPower arcadeDrive(double lefty, double leftx) { 
	motorPower power;
	power.leftmotor = lefty+leftx;
	power.rightmotor = lefty-leftx;
	return power;
 }

 motorPower tankDrive(double lefty, double righty) {
	motorPower power;
	power.leftmotor = lefty;
	power.rightmotor = righty;
	return power;
 }

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor fleft_mtr(11);
	pros::Motor bleft_mtr(20);
	pros::Motor_Group left_mtr({fleft_mtr, bleft_mtr});
	
	pros::Motor fright_mtr(1);
	pros::Motor bright_mtr(6);
	bright_mtr.set_reversed(true);;
	fright_mtr.set_reversed(true);
	pros::Motor_Group right_mtr({fright_mtr, bright_mtr});

	pros::Motor elevate_mtr(8);

	elevate_mtr.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

	while (true) {
		using namespace pros;
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		
		// drivetrain, arcade drive
		// left controls fwd/bwd, right controls turning
		double lefty = master.get_analog(ANALOG_RIGHT_X);
		double leftx = master.get_analog(ANALOG_LEFT_Y);
		motorPower power = arcadeDrive(leftx, lefty);
		left_mtr.move(power.leftmotor);
		right_mtr.move(power.rightmotor);

		// elevate_mtr
		int elevate_velocity = 300;
		if (master.get_digital(DIGITAL_R1)) {
			elevate_mtr.move_velocity(elevate_velocity);
		} else if (master.get_digital(DIGITAL_R2)) {
			elevate_mtr.move_velocity(-elevate_velocity);
		} else {
			elevate_mtr.move_velocity(0);
		}

		pros::delay(5);
	}
}
