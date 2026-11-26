//package esiot.sweeping_system;

/**
 * 
 * An example of Dashboard for the Sweeping Case Study
 * 
 * Partially implemented.
 * 
 */
class DashboardLauncher   {

	static Dashboard view = null;

	public static void main(String[] args) throws Exception {	
		/*
		if (args.length != 1){
			System.err.println("Args: <serial port>");
			System.exit(1);
		}*/

	    view = new Dashboard();
		
		String portName = "COM5";
		DashboardController contr = new DashboardController(portName,view);
		view.registerController(contr);
		
		view.display();
	}
}