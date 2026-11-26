import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.LayoutManager;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.LinkedList;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;

class Dashboard extends JFrame implements ActionListener  {

	private String[] column = {"Sector", "Obj. detected", "Distance"};
	private DefaultTableModel model = new DefaultTableModel(column, 0); 
	
	private JTextField currentState;
	
	
	private DashboardController controller;	
	
	public Dashboard(){
    super(".:: Radar Dashboard ::.");

    setSize(600,800);
    this.setResizable(false);

    JPanel mainPanel = new JPanel();
    mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));

    mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

    JPanel infoLine = new JPanel();
    infoLine.setLayout(new BoxLayout(infoLine, BoxLayout.LINE_AXIS));

    currentState = new JTextField("--");
    currentState.setEditable(false);
    currentState.setPreferredSize(new Dimension(200,15));

    infoLine.add(new JLabel("Current State:"));
    infoLine.add(currentState);

    mainPanel.add(infoLine);
    mainPanel.add(Box.createRigidArea(new Dimension(0,20)));

    // CREAZIONE TABELLA
    JTable sectorTable = new JTable(model);

    sectorTable.setFillsViewportHeight(true);

    JScrollPane scrollPane = new JScrollPane(sectorTable);

    mainPanel.add(scrollPane);

    setContentPane(mainPanel);

    addWindowListener(new WindowAdapter(){
        public void windowClosing(WindowEvent ev){
            System.exit(-1);
        }
    });
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
			  /*
			  if (ev.getSource() == ...){
			  */ 
		  } catch (Exception ex){
			  ex.printStackTrace();

		  }
	}
}