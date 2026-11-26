//package esiot.sweeping_system;

public class DashboardController  {

	SerialCommChannel channel;
	Dashboard view;
	//LogView logger;
	
	public DashboardController(String port, Dashboard view) throws Exception {
		this.view = view;
		
		channel = new SerialCommChannel(port,115200);		
		new MonitoringAgent(channel,view).start();
		
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");			
	}
	
}