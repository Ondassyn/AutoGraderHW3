import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeoutException;

public class MainActivity {

	private static BufferedWriter listWriter;
	private static BufferedReader listReader;

	public static void main(String[] args) throws InterruptedException, IOException {
		// TODO Auto-generated method stub

		listWriter = new BufferedWriter(new FileWriter("list_of_perfect_testers.txt"));
		listWriter.write("List of successful testers\n\n");

		listReader = new BufferedReader(new FileReader("list_compiled.txt"));
		if (listReader == null || listWriter == null) {
			System.out.println("Could not open " + listReader);
			return;

		}
		String line;
		while ((line = listReader.readLine()) != null) {
			// if(!file.getName().contains("Abyl")) continue;

			System.out.println("\n\n	~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			System.out.println("File path: { " + line + " }");

			try {
				ProcessHandler processHandler = new ProcessHandler(line, listWriter);
			} catch (IOException | TimeoutException | ExecutionException | NullPointerException e) {
				// TODO Auto-generated catch block
				System.out.println("PROCESS HANDLING ERROR:\n" + e);
			}
		}

		listWriter.close();
		listReader.close();

	}

}
