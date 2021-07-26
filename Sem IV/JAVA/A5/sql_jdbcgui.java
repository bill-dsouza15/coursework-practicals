import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Color;

import javax.swing.JTextField;
import javax.swing.SwingConstants;

import net.proteanit.sql.DbUtils;

import java.awt.Font;
import javax.swing.JButton;
import javax.swing.JTable;
import java.sql.*;

public class DatabaseMain {
	private static JTextField IGrNo;
	private static JTextField UGrNo;
	private static JTextField IName;
	private static JTextField IMob;
	private static JTextField IAddr;
	private static JTextField DGrNo;
	static Connection conn = null;
	static Statement st = null;
	static PreparedStatement pst = null;
	private static JTextField UName;
	private static JTextField UMob;
	private static JTextField UAddr;
	
	//////////////////////////////////////////////// INSERT //////////////////////////////////////////////////
	
	public static void insertProc(JTabbedPane tabbedPane, Statement st, Connection conn, JFrame frame) 
	{
		JPanel InsertPanel;
		InsertPanel = new JPanel();
		tabbedPane.addTab("Insert", null, InsertPanel, "Insert Record");
		InsertPanel.setLayout(null);
		JLabel InsertGr = new JLabel("GrNo");
		InsertGr.setFont(new Font("Cantarell", Font.BOLD, 15));
		InsertGr.setBounds(90, 53, 100, 30);
		InsertPanel.add(InsertGr);
		
		JLabel InsertName = new JLabel("Name");
		InsertName.setFont(new Font("Cantarell", Font.BOLD, 15));
		InsertName.setBounds(90, 103, 100, 30);
		InsertPanel.add(InsertName);
		
		JLabel InsertMob = new JLabel("Mobile No.");
		InsertMob.setFont(new Font("Cantarell", Font.BOLD, 15));
		InsertMob.setBounds(90, 153, 100, 30);
		InsertPanel.add(InsertMob);
		
		JLabel InsertAdd = new JLabel("Address");
		InsertAdd.setFont(new Font("Cantarell", Font.BOLD, 15));
		InsertAdd.setBounds(90, 203, 100, 30);
		InsertPanel.add(InsertAdd);
		
		IGrNo = new JTextField();
		IGrNo.setText("Enter GrNo");
		IGrNo.setHorizontalAlignment(SwingConstants.CENTER);
		IGrNo.setFont(new Font("Cantarell", Font.ITALIC, 13));
		IGrNo.setBounds(210, 53, 160, 30);
		IGrNo.setFocusable(false);
		IGrNo.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				IGrNo.setFocusable(true);
				IGrNo.setText(null);
				IGrNo.setFont(new Font("Cantarell", Font.PLAIN, 14));
			}
		});
		InsertPanel.add(IGrNo);
		IGrNo.setColumns(10);
		
		IName = new JTextField();
		IName.setText("Enter Name");
		IName.setHorizontalAlignment(SwingConstants.CENTER);
		IName.setFont(new Font("Cantarell", Font.ITALIC, 13));
		IName.setBounds(210, 103, 160, 30);
		IName.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				IName.setText(null);
				IName.setFont(new Font("Cantarell", Font.PLAIN, 14));
			}
		});
		InsertPanel.add(IName);
		IName.setColumns(10);
		
		IMob = new JTextField();
		IMob.setText("Enter Mobile No.");
		IMob.setHorizontalAlignment(SwingConstants.CENTER);
		IMob.setFont(new Font("Cantarell", Font.ITALIC, 13));
		IMob.setBounds(210, 153, 160, 30);
		IMob.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				IMob.setText(null);
				IMob.setFont(new Font("Cantarell", Font.PLAIN, 14));
			}
		});
		InsertPanel.add(IMob);
		IMob.setColumns(10);
		
		IAddr = new JTextField();
		IAddr.setText("Enter Address");
		IAddr.setHorizontalAlignment(SwingConstants.CENTER);
		IAddr.setFont(new Font("Cantarell", Font.ITALIC, 13));
		IAddr.setBounds(210, 203, 160, 30);
		IAddr.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				IAddr.setText(null);
				IAddr.setFont(new Font("Cantarell", Font.PLAIN, 14));
			}
		});
		InsertPanel.add(IAddr);
		IAddr.setColumns(10);
		
		JButton InsertButton = new JButton("Insert");
		InsertButton.setBounds(90, 271, 114, 25);
		InsertButton.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				final String grno = IGrNo.getText();
				final String name = IName.getText();
				final String mobno = IMob.getText();
				final String address = IAddr.getText();
				if(!grno.isEmpty() && !name.isEmpty() && !mobno.isEmpty() && !address.isEmpty())
				{
					try
					{
						pst = conn.prepareStatement("INSERT INTO Student_info (GrNo,Name,MobileNo,Address) VALUES(?,?,?,?);");
						pst.setString(1, grno);
						pst.setString(2, name);
						pst.setString(3, mobno);
						pst.setString(4, address);
						pst.executeUpdate();
						IGrNo.setText(null);
						IName.setText(null);
						IMob.setText(null);
						IAddr.setText(null);
						JOptionPane.showMessageDialog(frame, "      RECORD INSERTED!");
					}
					catch(SQLException e)
					{
						e.printStackTrace();
						JOptionPane.showMessageDialog(frame, " RECORD ALREADY EXISTS!");
						IGrNo.setText(null);
						IName.setText(null);
						IMob.setText(null);
						IAddr.setText(null);
					}
				}
				else
				{
					JOptionPane.showMessageDialog(frame, " NO FIELD MUST BE BLANK!");
				}
			}
		});
		InsertPanel.add(InsertButton);
		
		JButton ClearButton = new JButton("Clear All");
		ClearButton.setBounds(256, 271, 114, 25);
		ClearButton.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				IGrNo.setText(null);
				IName.setText(null);
				IMob.setText(null);
				IAddr.setText(null);
			}
		});
		InsertPanel.add(ClearButton);
	}
	
	//////////////////////////////////////////////// DISPLAY //////////////////////////////////////////////////
	
	public static void displayProc(JTabbedPane tabbedPane, Statement st, Connection conn, JFrame frame)
	{	
		JPanel DisplayPanel, ButtonPanel;
		DisplayPanel = new JPanel();
		ButtonPanel = new JPanel();
		tabbedPane.addTab("Display", null, DisplayPanel, "Display Table");
		
		DisplayPanel.setLayout(new BorderLayout());
		ButtonPanel.setLayout(new BorderLayout());
		
		JButton DispButton = new JButton("Display");
		
		JTable table = new JTable();
		table.setEnabled(false);
		ButtonPanel.add(DispButton, BorderLayout.CENTER);
		DisplayPanel.add(ButtonPanel, BorderLayout.SOUTH);
		JScrollPane scrollPane;
		scrollPane = new JScrollPane(table);
		DisplayPanel.add(scrollPane, BorderLayout.CENTER);
		DispButton.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				ResultSet rs;
				try
				{
					rs = st.executeQuery("SELECT * FROM Student_info;");
					table.setModel(DbUtils.resultSetToTableModel(rs));
					rs.close();
				}
				catch(Exception e)
				{
					e.printStackTrace();
				}
			}
		});
	}
	
	//////////////////////////////////////////////// UPDATE //////////////////////////////////////////////////
	
	public static void updateProc(JTabbedPane tabbedPane, Statement st, Connection conn, JFrame frame)
	{
		JPanel UpdatePanel;
		UpdatePanel = new JPanel();
		tabbedPane.addTab("Update", null, UpdatePanel, "Update Record");
		UpdatePanel.setLayout(null);
		
		JLabel UpdateGr = new JLabel("GrNo");
		UpdateGr.setFont(new Font("Cantarell", Font.BOLD, 15));
		UpdateGr.setBounds(90, 23, 100, 30);
		UpdatePanel.add(UpdateGr);
		
		UGrNo = new JTextField();
		UGrNo.setText("Enter GrNo");
		UGrNo.setHorizontalAlignment(SwingConstants.CENTER);
		UGrNo.setFont(new Font("Cantarell", Font.ITALIC, 13));
		UGrNo.setBounds(210, 23, 160, 30);
		UGrNo.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				UGrNo.setFocusable(true);
				UGrNo.setText(null);
				UGrNo.setFont(new Font("Cantarell", Font.PLAIN, 14));
			}
		});
		UpdatePanel.add(UGrNo);
		UGrNo.setColumns(10);
		
		JLabel UpdateName = new JLabel("Name");
		UpdateName.setFont(new Font("Cantarell", Font.BOLD, 15));
		UpdateName.setBounds(90, 150, 100, 30);
		UpdatePanel.add(UpdateName);
		
		JLabel UpdateMob = new JLabel("Mobile No.");
		UpdateMob.setFont(new Font("Cantarell", Font.BOLD, 15));
		UpdateMob.setBounds(90, 200, 100, 30);
		UpdatePanel.add(UpdateMob);
		
		JLabel UpdateAddr = new JLabel("Address");
		UpdateAddr.setFont(new Font("Cantarell", Font.BOLD, 15));
		UpdateAddr.setBounds(90, 250, 100, 30);
		UpdatePanel.add(UpdateAddr);
		
		JLabel UpdateGuide = new JLabel("Enter only fields to be updated");
		UpdateGuide.setBounds(122, 121, 226, 15);
		UpdatePanel.add(UpdateGuide);
		
		UName = new JTextField();
		UName.setText(null);
		UName.setHorizontalAlignment(SwingConstants.CENTER);
		UName.setColumns(10);
		UName.setBounds(210, 150, 160, 30);
		UName.setEditable(false);
		UName.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				UName.setFocusable(true);
				UName.setText(null);
				UName.setFont(new Font("Cantarell", Font.PLAIN, 14));
			}
		});
		UpdatePanel.add(UName);
		
		UMob = new JTextField();
		UMob.setText(null);
		UMob.setHorizontalAlignment(SwingConstants.CENTER);
		UMob.setFont(new Font("Cantarell", Font.ITALIC, 13));
		UMob.setColumns(10);
		UMob.setBounds(210, 200, 160, 30);
		UMob.setEditable(false);
		UMob.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				UMob.setFocusable(true);
				UMob.setText(null);
				UMob.setFont(new Font("Cantarell", Font.PLAIN, 14));
			}
		});
		UpdatePanel.add(UMob);
		
		UAddr = new JTextField();
		UAddr.setText(null);
		UAddr.setHorizontalAlignment(SwingConstants.CENTER);
		UAddr.setFont(new Font("Cantarell", Font.ITALIC, 13));
		UAddr.setColumns(10);
		UAddr.setBounds(210, 250, 160, 30);
		UAddr.setEditable(false);
		UAddr.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				UAddr.setFocusable(true);
				UAddr.setText(null);
				UAddr.setFont(new Font("Cantarell", Font.PLAIN, 14));
			}
		});
		UpdatePanel.add(UAddr);
		
		JButton UClearButton = new JButton("Clear All");
		UClearButton.setBounds(256, 304, 114, 25);
		UClearButton.setEnabled(false);
		UClearButton.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				UName.setText(null);
				UMob.setText(null);
				UAddr.setText(null);
			}
		});
		UpdatePanel.add(UClearButton);
		
		JButton UpdateButton = new JButton("Update");
		UpdateButton.setBounds(90, 304, 114, 25);
		UpdateButton.setEnabled(false);
		UpdateButton.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				final String name = UName.getText();
				final String mob = UMob.getText();
				final String addr = UAddr.getText();
				final String grno = (UpdateGuide.getText()).substring(7, (UpdateGuide.getText()).length());
				try
				{	
					if(name.isEmpty() && mob.isEmpty() && addr.isEmpty())
					{
						JOptionPane.showMessageDialog(frame, " ATLEEAST ONE FIELD NEEDED!");
					}
					else
					{
						if(!name.isEmpty() && !mob.isEmpty() && addr.isEmpty())
						{
							pst = conn.prepareStatement("UPDATE Student_info SET Name=?, MobileNo=? WHERE GrNo=?");
							pst.setString(1, name);
							pst.setString(2, mob);
							pst.setString(3, grno);
							pst.executeUpdate();
						}
						else if(!name.isEmpty() && mob.isEmpty() && !addr.isEmpty())
						{
							pst = conn.prepareStatement("UPDATE Student_info SET Name=?, Address=? WHERE GrNo=?");
							pst.setString(1, name);
							pst.setString(2, addr);
							pst.setString(3, grno);
							pst.executeUpdate();
						}
						else if(name.isEmpty() && !mob.isEmpty() && !addr.isEmpty())
						{
							pst = conn.prepareStatement("UPDATE Student_info SET MobileNo=?, Address=? WHERE GrNo=?");
							pst.setString(1, mob);
							pst.setString(2, addr);
							pst.setString(3, grno);
							pst.executeUpdate();
						}
						else if(!name.isEmpty() && mob.isEmpty() && addr.isEmpty())
						{
							pst = conn.prepareStatement("UPDATE Student_info SET Name=? WHERE GrNo=?");
							pst.setString(1, name);
							pst.setString(2, grno);
							pst.executeUpdate();
						}
						else if(name.isEmpty() && !mob.isEmpty() && addr.isEmpty())
						{
							pst = conn.prepareStatement("UPDATE Student_info SET MobileNo=? WHERE GrNo=?");
							pst.setString(1, mob);
							pst.setString(2, grno);
							pst.executeUpdate();
						}
						else if(name.isEmpty() && mob.isEmpty() && !addr.isEmpty())
						{
							pst = conn.prepareStatement("UPDATE Student_info SET Address=? WHERE GrNo=?");
							pst.setString(1, addr);
							pst.setString(2, grno);
							pst.executeUpdate();
						}
						else if(!name.isEmpty() && !mob.isEmpty() && !addr.isEmpty())
						{
							pst = conn.prepareStatement("UPDATE Student_info SET Name=?, MobileNo=?, Address=? WHERE GrNo=?");
							pst.setString(1, name);
							pst.setString(2, mob);
							pst.setString(3, addr);
							pst.setString(4, grno);
							pst.executeUpdate();
						}
						JOptionPane.showMessageDialog(frame, "   RECORD UPDATED!");
						UName.setText(null);
						UMob.setText(null);
						UAddr.setText(null);
						UpdateGuide.setText("Enter only fields to be updated");
						UName.setEditable(false);
						UMob.setEditable(false);
						UAddr.setEditable(false);
						UpdateButton.setEnabled(false);
						UClearButton.setEnabled(false);
					}
				}
				catch(SQLException e)
				{
					e.printStackTrace();
				}
			}
		});
		UpdatePanel.add(UpdateButton);
		
		JButton CheckButton = new JButton("Check");
		CheckButton.setBounds(176, 65, 114, 25);
		CheckButton.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				final String grno = UGrNo.getText();
				ResultSet rs;
				int count = 0;
				if(!grno.isEmpty())
				{
					try
					{
						rs = st.executeQuery("SELECT COUNT(GrNo) FROM Student_info WHERE GrNo="+grno);
						while(rs.next())
						{
							count = rs.getInt("COUNT(GrNo)");
						}
						if(count>0)
						{
							JOptionPane.showMessageDialog(frame, "   RECORD FOUND!");
							UpdateGuide.setText("GrNo : "+grno);
							UGrNo.setText(null);
							UName.setEditable(true);
							UMob.setEditable(true);
							UAddr.setEditable(true);
							UpdateButton.setEnabled(true);
							UClearButton.setEnabled(true);
						}
						else
						{
							JOptionPane.showMessageDialog(frame, " RECORD DOES NOT EXISTS!");
							UGrNo.setText(null);
						}
					}
					catch(SQLException e)
					{
						e.printStackTrace();
					}
				}
				else
				{
					JOptionPane.showMessageDialog(frame, " FIELD MUST NOT BE BLANK!");
				}
			}
		});
		UpdatePanel.add(CheckButton);
	}
	
	//////////////////////////////////////////////// DELETE //////////////////////////////////////////////////
	
	public static void deleteProc(JTabbedPane tabbedPane, Statement st, Connection conn, JFrame frame)
	{
		JPanel DeletePanel;
		DeletePanel = new JPanel();
		tabbedPane.addTab("Delete", null, DeletePanel, "Delete Record");
		DeletePanel.setLayout(null);
		
		JLabel DeleteGr = new JLabel("GrNo");
		DeleteGr.setFont(new Font("Cantarell", Font.BOLD, 15));
		DeleteGr.setBounds(90, 103, 100, 30);
		DeletePanel.add(DeleteGr);
		
		DGrNo = new JTextField();
		DGrNo.setText("Enter Gr No.");
		DGrNo.setHorizontalAlignment(SwingConstants.CENTER);
		DGrNo.setFont(new Font("Cantarell", Font.ITALIC, 13));
		DGrNo.setBounds(210, 103, 140, 30);
		DGrNo.setFocusable(false);
		DGrNo.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				DGrNo.setText(null);
				DGrNo.setFocusable(true);
				DGrNo.setFont(new Font("Cantarell", Font.PLAIN, 14));
			}
		});
		DeletePanel.add(DGrNo);
		DGrNo.setColumns(10);
		
		JButton DeleteButton = new JButton("Delete");
		DeleteButton.setBounds(170, 168, 114, 25);
		DeleteButton.addMouseListener(new MouseAdapter()
		{
			@Override
			public void mouseClicked(MouseEvent ev)
			{
				final String grno = DGrNo.getText();
				if(!grno.isEmpty())
				{
					try
					{
						String temp="";
						int v1 = 0,v2 = 0;
						ResultSet rs;
						rs = st.executeQuery("SELECT COUNT(SrNo) FROM Student_info;");
						while(rs.next())
						{
							temp = String.valueOf(rs.getInt("COUNT(SrNo)"));
						}
						if(temp!=null)
						{
							v1 = Integer.parseInt(temp);
						}
						
						pst = conn.prepareStatement("DELETE FROM Student_info WHERE GrNo = ?;");
						pst.setString(1, grno);
						pst.executeUpdate();
						DGrNo.setText(null);
						
						rs = st.executeQuery("SELECT COUNT(SrNo) FROM Student_info;");
						while(rs.next())
						{
							temp = String.valueOf(rs.getInt("COUNT(SrNo)"));
						}
						if(temp!=null)
						{
							v2 = Integer.parseInt(temp);
						}
						
						if(v1-v2 == 1)
						{
							JOptionPane.showMessageDialog(frame, "     RECORD DELETED!");
						}
						else
						{
							JOptionPane.showMessageDialog(frame, "  RECORD DOES NOT EXIST!");
						}
					}
					catch(SQLException e)
					{
						e.printStackTrace();
					}
				}
				else
				{
					JOptionPane.showMessageDialog(frame, "FIELD MUST NOT BE BLANK!");
				}
			}
		});
		DeletePanel.add(DeleteButton);
	}
	
	//////////////////////////////////////////////// INITIALIZE //////////////////////////////////////////////////
	
	private static void initialize(Statement st, Connection conn) 
	{
		final JFrame frame = new JFrame();
		frame.setBounds(100, 100, 460, 400);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getSize();
		frame.setLocationRelativeTo(null);
		frame.setTitle("StudentDatabase");
		frame.setVisible(true);
		frame.getContentPane().setLayout(new GridLayout(1,1));
		JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		tabbedPane.setBackground(Color.WHITE);
		
		try
		{
			st.executeUpdate("CREATE TABLE Student_info(SrNo INT NOT NULL AUTO_INCREMENT,GrNo VARCHAR(8) NOT NULL,Name VARCHAR(20) NOT NULL,MobileNo VARCHAR(10) NOT NULL,Address VARCHAR(50) NOT NULL,PRIMARY KEY(SrNo,GrNo))");
			st.executeUpdate("CREATE UNIQUE INDEX uniGr ON Student_info(GrNo)");
		}
		catch(SQLException e)
		{
			e.printStackTrace();
		}
		
		////////////////Insert Records//////////////////
		
		insertProc(tabbedPane,st,conn,frame);
		
		//////////////// Display Records//////////////////
		
		displayProc(tabbedPane,st,conn,frame);
		
		//////////////// Update Records //////////////////
		
		updateProc(tabbedPane,st,conn,frame);
		
		////////////////Update Records //////////////////
		
		deleteProc(tabbedPane,st,conn,frame);
		
		/////////////////////////////////////////////////
		
		frame.getContentPane().add(tabbedPane);	
	}
	
	//////////////////////////////////////////////// MAIN //////////////////////////////////////////////////
	
	public static void main(String[] args) 
	{
		EventQueue.invokeLater(new Runnable() {
			public void run() 
			{
				try
				{
					Class.forName("com.mysql.cj.jdbc.Driver");
				}
				catch(Exception e)
				{
					e.printStackTrace();
				}
				try
				{
					String url = "jdbc:mysql://localhost:3306/student"; 
					String uname = "root";
					String pswd = "mysqlroot";
				   	//Create connection to sql//	
			    	conn = DriverManager.getConnection(url,uname,pswd);
			    	st = conn.createStatement();			    	
				}
				catch(SQLException e)
				{
					e.printStackTrace();
				}
				initialize(st,conn);
			}
		});
	}
}

	
