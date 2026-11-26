//package esiot.sweeping_system;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	Dashboard view;
	
	static final String SECTOR_PREFIX	=  "sct:";
	static final String STATE_PREFIX 	=  "st:";
	static final String RADAR_INFO_PREFIX 	=  "rdr:";
	static final String INFO_SEPARATOR 	=  "|";

	private int create = 0;

	
	
	public MonitoringAgent(SerialCommChannel channel, Dashboard view) throws Exception {
		this.view = view;
		this.channel = channel;
	}
	
	public void run(){
		
		while (true){
			try {
				String msg = channel.receiveMsg();
				
				if (msg.startsWith(SECTOR_PREFIX) && create == 0){
					create ++;
					String sectors = msg.substring(SECTOR_PREFIX.length()); 
                    view.createSectorTable(Integer.valueOf(sectors));		

				} else if (msg.startsWith(STATE_PREFIX)){
					String state = msg.substring(STATE_PREFIX.length()); 
                    view.updateState(state);
					
				} else if (msg.startsWith(RADAR_INFO_PREFIX)){
					String info = msg.substring(4);
					String sector = info.substring(0, info.indexOf(INFO_SEPARATOR));
					info = info.substring(info.indexOf(INFO_SEPARATOR)+1);
					String object = info.substring(0, info.indexOf(INFO_SEPARATOR));
					info = info.substring(info.indexOf(INFO_SEPARATOR) + 1);
                    view.updateSectorTable(Integer.valueOf(sector), object, info);
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}

}