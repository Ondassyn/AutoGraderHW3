import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Compiler {

	private static final Object processLock = new Object();
	private static ProcessBuilder processBuilder;
	private static Process process;
	private static BufferedWriter listWriter;
	private static BufferedWriter anotherListWriter;
	
	public static void main(String[] args) throws IOException, InterruptedException {
		// TODO Auto-generated method stub
		String currentDirName = System.getProperty("user.dir");
		File submDir  = new File(currentDirName + "\\submissions");
		
		File[] dirs = submDir.listFiles();
		
		listWriter = new BufferedWriter(new FileWriter("list_compiled.txt"));
		anotherListWriter = new BufferedWriter(new FileWriter("list_not_complied.txt"));
		
		System.out.println("Compiling {start} ...\n");
		
		for(File file: dirs) {
			synchronized (processLock) {
			String[] files = file.list();
			String filename = "";
			System.out.println("Folder name: { " + file.getName() + " }");
			
			for (String str: files) {
				if(str.contains(".c")) {
					filename = str;
					break;
				}
			}
			
			if(filename == "") {
				anotherListWriter.write(file.getAbsolutePath());
				System.out.println("	==> ERROR: No .c file is found");
				continue;
			}
			
			String path = file.getAbsolutePath() + "\\" + filename;
			
			String exePath = path.substring(0, path.length()-1) + "exe";
			
			processBuilder = new ProcessBuilder("gcc", "-std=c99", "-o", exePath, "\"" + path + "\"");
		
			process = processBuilder.start();
			
			String[] againFiles = file.list();
			
			for (String str: againFiles) {
				if(str.contains(".exe")) {
					listWriter.write(exePath + "\n");
				}
			}
			
			int wf = process.waitFor();
			
//			process.destroy();
//			if(process.isAlive())
//				process.destroyForcibly();
		}
		}
		
		listWriter.close();
		System.out.println("\nCompiling {finish} ...");
	}

}
