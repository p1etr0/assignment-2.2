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

	public void stopAction() {
		channel.sendMsg("stp");
	}

	public void resetAction() {
		channel.sendMsg("rst");
	}

    public void rightSweepAction() {
        channel.sendMsg("rs");
    }

    public void leftSweepAction() {
        channel.sendMsg("ls");
    }

	public void takeControlAction() {
		channel.sendMsg("tc");
	}

    public void releaseControlAction() {
        channel.sendMsg("rc");
    }
	
}