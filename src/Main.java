import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.InputEvent;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Main {

	public static void main(String[] args) throws AWTException, FileNotFoundException, IOException, InterruptedException {
		Robot robot = new Robot();
		
		int startX = Integer.parseInt(args[0]);
		int startY = Integer.parseInt(args[1]);
		int delay = Integer.parseInt(args[2]);

		Thread.sleep(1000);
		
		try (BufferedReader br = new BufferedReader(new FileReader(".tempsave.txt"))) {
            String line;
            int lineNumber = 0;
            while ((line = br.readLine()) != null) {
                if (line.isEmpty()) {
                    continue; // Skip empty lines
                }
            	
            	line = line.replace("\n", "");
                String[] moves = line.split(";");
                for(int i = 0; i < moves.length; i++) {
                	String[] values = moves[i].split(":");
                	int streamStart = Integer.parseInt(values[0]);
                	int streamEnd = Integer.parseInt(values[1]);
                	
                	robot.mouseMove(startX + streamStart, startY + lineNumber);
                	Thread.sleep(5);
                	robot.mousePress(InputEvent.BUTTON1_DOWN_MASK);
                	Thread.sleep(5);
                	robot.mouseMove(startX + streamEnd, startY + lineNumber);
                	Thread.sleep(5);
                	robot.mouseRelease(InputEvent.BUTTON1_DOWN_MASK);
                	Thread.sleep(5);
                	
                	Thread.sleep(delay);
                }
                
                lineNumber++;
            }
        }
	}

}
