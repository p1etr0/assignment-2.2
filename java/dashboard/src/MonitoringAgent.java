//package esiot.sweeping_system;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	Dashboard view;
	
	static final String APP_PREFIX 	=  "sw:";
	static final String LOG_PREFIX 	=  "lo:";
	
	
	public MonitoringAgent(SerialCommChannel channel, Dashboard view) throws Exception {
		this.view = view;
		this.channel = channel;
	}
	
	public void run(){
		while (true){
			try {
				String msg = channel.receiveMsg();
				// logger.log("new msg: "+msg);				
				if (msg.startsWith(APP_PREFIX)){
					String cmd = msg.substring(APP_PREFIX.length()); 
                    view.updateSweepingCount(cmd);
					//logger.log("new command: "+cmd);				

				} else if (msg.startsWith(LOG_PREFIX)){
					//this.logger.log(msg.substring(LOG_PREFIX.length()));
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}

}