import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;

class Dashboard extends JFrame implements ActionListener  {	
	private DashboardController controller;	
	
	private JTextField currentState;

	private JButton stop;
	private JButton reset;
	private JButton rightSweep;
	private JButton leftSweep;
	private JButton takeControl;
	private JButton releaseControl;

	private String[] column = {"Sector", "Obj. detected", "Distance"};
	private DefaultTableModel model = new DefaultTableModel(column, 0); 


	public Dashboard(){
    	super("Radar Dashboard");
    	setSize(600,800);
    	this.setResizable(false);

    	JPanel mainPanel = new JPanel();
    	mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));

    	//mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
    	JPanel infoLine = new JPanel();
    	infoLine.setLayout(new BoxLayout(infoLine, BoxLayout.LINE_AXIS));

    	currentState = new JTextField("--");
    	currentState.setEditable(false);
    	currentState.setMaximumSize(new Dimension(500,25));

    	infoLine.add(new JLabel("CURRENT SECTOR:"));
    	infoLine.add(currentState);

    	mainPanel.add(infoLine);
    	mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
		JPanel controlPanel = new JPanel();
    	controlPanel.setLayout(new BoxLayout(controlPanel, BoxLayout.LINE_AXIS));

		stop = new JButton();
		stop.setText("STOP");
		stop.setPreferredSize(new Dimension(100,20));
		reset = new JButton();
		reset.setText("RESET");
		reset.setPreferredSize(new Dimension(100,20));
		rightSweep = new JButton();
		rightSweep.setText("->");
		rightSweep.setPreferredSize(new Dimension(100,20));
		leftSweep = new JButton();
		leftSweep.setText("<-");
		leftSweep.setPreferredSize(new Dimension(100,20));
		takeControl = new JButton();
		takeControl.setText("TAKE CONTROL");
		takeControl.setPreferredSize(new Dimension(100,20));
		releaseControl = new JButton();
		releaseControl.setText("RELEASE CONTROL");
		releaseControl.setPreferredSize(new Dimension(100,20));

		controlPanel.add(stop);
		controlPanel.add(reset);
		controlPanel.add(rightSweep);
		controlPanel.add(leftSweep);
		controlPanel.add(takeControl);
		controlPanel.add(releaseControl);

		mainPanel.add(controlPanel);
		mainPanel.add(Box.createRigidArea(new Dimension(0,20)));
		JPanel contentTable = new JPanel();
    	contentTable.setLayout(new BoxLayout(contentTable, BoxLayout.LINE_AXIS));

    	JTable sectorTable = new JTable(model);
    	sectorTable.setFillsViewportHeight(true);
		sectorTable.setPreferredSize(new Dimension(500,500));

    	JScrollPane scrollPane = new JScrollPane(sectorTable);

		contentTable.add(scrollPane);
    	//mainPanel.add(scrollPane);
		mainPanel.add(contentTable);
		setEnabledButton(false, false, false, false, true, false);
    	setContentPane(mainPanel);
	
		stop.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				setEnabledButton(false, false, false, false, true, false);
				controller.stopAction();
			}

		});
		reset.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				controller.resetAction();
			}

		});
		rightSweep.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				controller.rightSweepAction();
			}

		});
		leftSweep.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				controller.leftSweepAction();
			}

		});

		takeControl.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (!currentState.getText().equals("IDLE")){
					setEnabledButton(true, true, true, true, false, true);
					controller.takeControlAction();
				}
			}

		});

		releaseControl.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				setEnabledButton(false, false, false, false, true, false);
				controller.releaseControlAction();
			}
		
		});

		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent ev){
				System.exit(-1);
			}
		});
	}

	private void setEnabledButton(boolean stop, boolean reset, boolean right, boolean left, boolean take, boolean release){
		this.stop.setEnabled(stop);
		this.reset.setEnabled(reset);
		this.rightSweep.setEnabled(right);
		this.leftSweep.setEnabled(left);
		this.takeControl.setEnabled(take);
		this.releaseControl.setEnabled(release);
	}
	
	public void display() {
		SwingUtilities.invokeLater(() -> {
			this.setVisible(true);
		});
	}

	public void registerController(DashboardController contr){
		this.controller = contr;
	}
	
	public void createSectorTable(int sectors){
		for (int i=0; i<sectors; i++){
			model.addRow(new Object[]{Integer.toString(i), "False", "--"});
		}
	}

	public void updateState(String state){
		SwingUtilities.invokeLater(() -> {
			currentState.setText(state);
		});
		
	}

	public void updateSectorTable(int sector, String object, String distance){
		SwingUtilities.invokeLater(() -> {
			model.setValueAt(object, sector, 1);
			model.setValueAt(distance, sector, 2);
		});
	}

	public void actionPerformed(ActionEvent ev){
		  try {
		  } catch (Exception ex){
			  ex.printStackTrace();
		  }
	}
}