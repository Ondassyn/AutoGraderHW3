import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.google.common.util.concurrent.SimpleTimeLimiter;
import com.google.common.util.concurrent.TimeLimiter;

import java.util.Random;

public class ProcessHandler {

	private ProcessBuilder processBuilder;
	private Process process;
	private InputStream stdout;
	private OutputStream stdin;
	private BufferedReader bufferedReader;
	private BufferedWriter bufferedWriter;
	private BufferedWriter fileWriter;

	private String password;

	private String inFilename;
	private String outFilename;
	private String deoutFilename;
	private String wrongFilename;
	private String preencFilename;
	private String predecFilename;
	
	private String inBigFilename;
	private String outBigFilename;
	private String deoutBigFilename;
	private String preencBigFilename;
	private String predecBigFilename;
	
	private TimeLimiter timeLimiter;

	byte[] buffer = new byte[512];

	private static boolean isAlive(Process p){
		try {
			p.exitValue();
			return false;
		} catch (IllegalThreadStateException e) {
			return true;
		}
	}

	private static boolean isFoundCaseInsensitive(String str, String substr){
		Pattern p = Pattern.compile(substr, Pattern.CASE_INSENSITIVE);
		Matcher m = p.matcher(str);

		if (m.find())
			return true;
		else
			return false;
	}

	private boolean isFoundNumber(String s) {
		Pattern p = Pattern.compile("[0-9]");
		Matcher m = p.matcher(s);

		return m.find();
	}

	private double findNumber(String str) {
		str = str.replaceAll("[^-?0-9]+", " ");
		String[] strs = str.trim().split(" ");
		if (strs.length > 1) {
			System.out.print("Found several numbers: { ");
			for (int i = 0; i < strs.length; i++) {
				System.out.print(strs[i] + " ");
			}
			System.out.println("}");
			return Double.parseDouble(strs[0]);
		} else if (strs.length == 1) {
			System.out.println("Found a number");
			return Double.parseDouble(strs[0]);
		} else {
			System.out.println("Found no number");
			return -1;
		}
	}

	private static boolean isFoundCaseSensitive(String str, String substr) {
		return str.contains(substr);
	}

	private void init(String path) throws IOException {
		System.out.println("Process initialization ...");
		fileWriter.write("Process initialization ...\n");

		processBuilder = new ProcessBuilder(path);


		processBuilder.redirectErrorStream(true);
		process = processBuilder.start();

		stdout = process.getInputStream();
		stdin = process.getOutputStream();

		bufferedReader = new BufferedReader(new InputStreamReader(stdout));
		bufferedWriter = new BufferedWriter(new OutputStreamWriter(stdin));
		
		timeLimiter = SimpleTimeLimiter.create(Executors.newCachedThreadPool());
		
		inFilename = "in.txt";
		wrongFilename = "wrongFile.txt";
		preencFilename = "out_preencrypted.txt";
		predecFilename = "deout_predecrypted.txt";
		
		inBigFilename = "big.txt";
		preencBigFilename = "big_out_preencrypted.txt";
		predecBigFilename = "big_deout_predecrypted.txt";
		
		password = "Q1w2E3";
	}

	public ProcessHandler(String path, BufferedWriter listWriter) throws IOException, InterruptedException, TimeoutException, ExecutionException {
		// TODO Auto-generated constructor stub
		String[] tokens = path.split("\\\\");
		String parentPath = "";
		String unedittedName = "";
		for(int i = 0; i < tokens.length - 1; i++ ) {
			if(i == tokens.length - 2) {
				unedittedName = tokens[i];
			}
			parentPath += (tokens[i] + "\\");
		}
		System.out.println(unedittedName + " " + parentPath);
		int i = 0;
		String name = "";
		char tempc;
		while((tempc = unedittedName.charAt(i)) != '_') {
			name += tempc;
			i++;
		}
		
		parentPath += "log.txt";	
		fileWriter = new BufferedWriter(new FileWriter(parentPath));
		
		String nameForFiles = name.replace(' ', '_');
		
		outFilename = nameForFiles + "_out.txt";
		deoutFilename = nameForFiles + "_deout.txt";
		outBigFilename = nameForFiles + "_big_out.txt";
		deoutBigFilename = nameForFiles + "_big_deout.txt";
		
		System.out.println("Start of process handling ...\nPath: { " + path + " }");
		fileWriter.write("Start of process handling ...\nPath: { " + path + " }\n");
		
		
		init(path);

		int ret = processProcess();
		
		if(ret == 0) {
			listWriter.write(name + "\n");
		}
		
		//bufferedWriter.close();
		//bufferedReader.close();
		
		process.destroy();
		if (process.isAlive())
			process.destroyForcibly();

		//process.waitFor();
		//destroyFiles();
		fileWriter.close();
	}

	private int processProcess() throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("\nProcessing begins ...");
		fileWriter.write("\nProcessing begins ...\n");
		// while(process.isAlive()) {
		
		int numberOfErrors = testPerfectCase();
		//int numberOfErrors = testImperfectCase();
		if (numberOfErrors == 0) {
			System.out.println("Perfect case result: SUCCESS");
			fileWriter.write("Perfect case result: SUCCESS\n");
		} else {
			System.out.println("Perfect case result: FAILURE. Number of errors : " + numberOfErrors);
			fileWriter.write("Perfect case result: FAILURE. Number of errors : " + numberOfErrors + "\n");
		}
		
		return numberOfErrors;
	}
	
	private int testPerfectCase() throws IOException {
		System.out.println("Testing with a certain scenario ...");
		fileWriter.write("Testing with a certain scenario ...\n");
		int errorNo = 18;
		try {
			if (checkString("welcome")) {
				errorNo--;
			}

			if (checkString("enter")) {
				errorNo--;
			}

			sendCommand(password);

			if (checkString("menu")) {
				errorNo--;
			}
				

			if(testUnrecognized() == 0) {
				errorNo--;
			}

			if (checkString("menu")) {
				errorNo--;
			}

			if(testEncryptWithNoFiles() == 0) {
				errorNo--;
			}

			if (checkString("menu")) {
				errorNo--;
			}
				
			if(testEncrypt() == 0) {
				errorNo--;
			}

			if (checkString("menu")){
				errorNo--;
			}
			
//			if(testEncryptBig() == 0) {
//				errorNo--;
//			}
//			
//			if (checkString("menu")){
//				errorNo--;
//			}

			if(testUnrecognized() == 0) {
				errorNo--;
			}

			if (checkString("menu")){
				errorNo--;
			}

			if(testDecryptWithNoFiles() == 0) {
				errorNo--;
			}

			if (checkString("menu")) {
				errorNo--;
			}

			if (testDecrypt() == 0) {
				errorNo--;
			}

			if (checkString("menu")){
				errorNo--;
			}
			
//			if (testDecryptBig() == 0) {
//				errorNo--;
//			}
//
//			if (checkString("menu")){
//				errorNo--;
//			}

			if (testUnrecognized() == 0) {
				errorNo--;
			}

			if (checkString("menu")) {
				errorNo--;
			}

			if (testQuit() == 0) {
				errorNo--;
			}

		} catch (IOException | InterruptedException | TimeoutException | ExecutionException e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
			System.out.println(e.getMessage());
			//fileWriter.write(e.getMessage());
			return errorNo;
		}
		
		return errorNo;
	}
	
	private int testImperfectCase() throws IOException {
		System.out.println("Testing with no scenario ...");
		fileWriter.write("Testing with no scenario ...\n");
		String[] commands = { "t", "e", "e", "2", "d", "d", "i", "q" };
		int index = 0;
		boolean withNonexFiles = true;
		// goes up with request, goes down with achievement
		int errorNo = 0;
		

		
		try {
			while (index < commands.length) {
				String resStr = returnString();
				if (resStr.equals("")) {
					System.out.println("Nothing to read ...");
					fileWriter.write("Nothing to read ...\n");
				} else if (isFoundCaseInsensitive(resStr, "welcome")) {
					System.out.println("The program: WELCOME ...");
					fileWriter.write("The program: WELCOME ...\n");
				} else if (isFoundCaseInsensitive(resStr, "enter")) {
					if (isFoundCaseInsensitive(resStr, "password")) {
						System.out.println("The program: PASSWORD");
						fileWriter.write("The program: PASSWORD\n");
						sendCommand(password);
					} else if (isFoundCaseInsensitive(resStr, "encrypt")) {
						System.out.println("The program: ENCRYPT");
						fileWriter.write("The program: ENCRYPT\n");
						testEncrypt();
					} else if (isFoundCaseInsensitive(resStr, "decrypt")) {
						System.out.println("The program: DECRYPT");
						fileWriter.write("The program: DECRYPT\n");
						testDecrypt();
					}
				} else if (isFoundCaseInsensitive(resStr, "menu")) {
					System.out.println("The program: MENU");
					fileWriter.write("The program: MENU\n");
					if (commands[index].equals("e")) {
						if (withNonexFiles) {
							testEncryptWithNoFiles();
						} else {
							testEncrypt();
						}
						withNonexFiles = !withNonexFiles;
					} else if (commands[index].equals("d")) {
						if (withNonexFiles) {
							testDecryptWithNoFiles();
						} else {
							testDecrypt();
						}
						withNonexFiles = !withNonexFiles;
					} else if (commands[index].equals("q")) {
						testQuit();
					} else {
						testUnrecognized();
					}
					index++;
				} else {
					System.out.println("Cannot understand the program");
					fileWriter.write("Cannot understand the program\n");
				}
			}

		} catch (IOException | InterruptedException | TimeoutException | ExecutionException e) {
			// TODO Auto-generated catch block
			// e.printStackTrace();
			System.out.println(e.getMessage());
			//fileWriter.write(e.getMessage());
			return errorNo;
		}

		return errorNo;
	}

	private int testQuit() throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("\nTesting quit ...");
		fileWriter.write("\nTesting quit ...\n");

		int errNo = 1;
		
		System.out.println("Testing quit: sending <q>");
		fileWriter.write("Testing quit: sending <q>");
		sendCommand("q");
		if (checkString("bye")) {
			System.out.println("Testing quit: SUCCESS");
			fileWriter.write("Testing quit: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing quit: FAILURE");
			fileWriter.write("Testing quit: FAILURE\n");
		}
		
		
		return errNo;
	}

	private int testEncrypt() throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("\nTesting encrypt ...");
		fileWriter.write("\nTesting encrypt ...\n");

		int errNo = 3;
		
		System.out.println("Testing encrypt: sending <e>");
		fileWriter.write("Testing encrypt: sending <e>\n");
		sendCommand("e");

		if (checkString("enter")) {
			System.out.println("Testing encrypt: SUCCESS");
			fileWriter.write("Testing encrypt: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing encrypt: FAILURE");
			fileWriter.write("Testing encrypt: FAILURE\n");
		}

		System.out.println("Testing encrypt: sending <" + inFilename + ">");
		fileWriter.write("Testing encrypt: sending <" + inFilename + ">\n");
		sendCommand(inFilename);

		if (checkString("enter")) {
			System.out.println("Testing encrypt: SUCCESS");
			fileWriter.write("Testing encrypt: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing encrypt: FAILURE");
			fileWriter.write("Testing encrypt: FAILURE\n");
		}
		System.out.println("Testing encrypt: sending <" + outFilename + ">");
		fileWriter.write("Testing encrypt: sending <" + outFilename + ">\n");
		sendCommand(outFilename);

		process.waitFor(1, TimeUnit.SECONDS);
		//process.waitFor();
		
		if (compareFilesFull(outFilename, preencFilename)) {
			System.out.println("Testing encrypt: SUCCESS");
			fileWriter.write("Testing encrypt: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing encrypt: FAILURE");
			fileWriter.write("Testing encrypt: FAILURE\n");
		}
		
		return errNo;
	}
	
	private int testEncryptBig() throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("\nTesting encrypt with a big file ...");
		fileWriter.write("\nTesting encrypt with a big file ...\n");

		int errNo = 5;
		
		System.out.println("Testing encrypt with a big file: sending <e>");
		fileWriter.write("Testing encrypt with a big file: sending <e>\n");
		sendCommand("e");

		if (checkString("enter")) {
			System.out.println("Testing encrypt with a big file: SUCCESS");
			fileWriter.write("Testing encrypt with a big file: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing encrypt with a big file: FAILURE");
			fileWriter.write("Testing encrypt with a big file: FAILURE\n");
		}

		System.out.println("Testing encrypt with a big file: sending <" + inBigFilename + ">");
		fileWriter.write("Testing encrypt with a big file: sending <" + inBigFilename + ">\n");
		sendCommand(inBigFilename);

		if (checkString("enter")) {
			System.out.println("Testing encrypt with a big file: SUCCESS");
			fileWriter.write("Testing encrypt with a big file: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing encrypt with a big file: FAILURE");
			fileWriter.write("Testing encrypt with a big file: FAILURE\n");
		}
		System.out.println("Testing encrypt with a big file: sending <" + outBigFilename + ">");
		fileWriter.write("Testing encrypt with a big file: sending <" + outBigFilename + ">\n");
		sendCommand(outBigFilename);

		process.waitFor(1, TimeUnit.SECONDS);
		//process.waitFor();
		
		if (compareFilesFull(outBigFilename, preencBigFilename)) {
			System.out.println("Testing encrypt with a big file: SUCCESS");
			fileWriter.write("Testing encrypt with a big file: SUCCESS\n");
			errNo--;
		} 
		else if (compareFilesSample(outBigFilename, preencBigFilename, 0.1)) {
			System.out.println("Testing encrypt with a big file 10%: ALMOST SUCCESS");
			fileWriter.write("Testing encrypt with a big file 10%: ALMOST SUCCESS\n");
			errNo--;
		}
		else if (compareFilesSample(outBigFilename, preencBigFilename, 0.5)) {
			System.out.println("Testing encrypt with a big file 50%: HALF SUCCESS");
			fileWriter.write("Testing encrypt with a big file 50%: HALF SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing encrypt with a big file: FAILURE");
			fileWriter.write("Testing encrypt with a big file: FAILURE\n");
		}
		
		return errNo;
	}

	private int testEncryptWithNoFiles()
			throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("\nTesting encrypt with non-existing files ...");
		fileWriter.write("\nTesting encrypt with non-existing files ...\n");
		
		int errNo = 2;
		
		System.out.println("Testing encrypt with non-existing files: sending <e>");
		fileWriter.write("Testing encrypt with non-existing files: sending <e>\n");
		sendCommand("e");

		if (checkString("enter")) {
			System.out.println("Testing encrypt with non-existing files: SUCCESS");
			fileWriter.write("Testing encrypt with non-existing files: SUCCESS\n");
			errNo--;
		} else {
			System.out.println("Testing encrypt with non-existing files: FAILURE");
			fileWriter.write("Testing encrypt with non-existing files: FAILURE\n");
		}
		System.out.println("Testing encrypt with non-existing files: sending <" + wrongFilename + ">");
		fileWriter.write("Testing encrypt with non-existing files: sending <" + wrongFilename + ">\n");
		sendCommand(wrongFilename);

		if (checkString("cannot")) {
			System.out.println("Testing encrypt with non-existing files: SUCCESS");
			fileWriter.write("Testing encrypt with non-existing files: SUCCESS\n");
			errNo--;
		} else {
			System.out.println("Testing encrypt with non-existing files: FAILURE");
			fileWriter.write("Testing encrypt with non-existing files: FAILURE\n");
		}
		
		return errNo;
	}

	private int testDecrypt() throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("\nTesting decrypt ...");
		fileWriter.write("\nTesting decrypt ...\n");

		int errNo = 3;
		
		System.out.println("Testing decrypt: sending <d>");
		fileWriter.write("Testing decrypt: sending <d>\n");
		sendCommand("d");

		if (checkString("enter")) {
			System.out.println("Testing decrypt: SUCCESS");
			fileWriter.write("Testing decrypt: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing decrypt: FAILURE");
			fileWriter.write("Testing decrypt: FAILURE\n");
		}
		System.out.println("Testing decrypt: sending <" + outFilename + ">");
		fileWriter.write("Testing decrypt: sending <" + outFilename + ">\n");
		sendCommand(outFilename);

		if (checkString("enter")) {
			System.out.println("Testing decrypt: SUCCESS");
			fileWriter.write("Testing decrypt: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing decrypt: FAILURE");
			fileWriter.write("Testing decrypt: FAILURE\n");
		}

		System.out.println("Testing decrypt: sending <" + deoutFilename + ">");
		fileWriter.write("Testing decrypt: sending <" + deoutFilename + ">\n");
		sendCommand(deoutFilename);

		process.waitFor(1, TimeUnit.SECONDS);
		//process.waitFor();
		
		if (compareFilesFull(deoutFilename, predecFilename)) {
			System.out.println("Testing decrypt: SUCCESS");
			fileWriter.write("Testing decrypt: SUCCESS\n");
			errNo--;
		} else {
			System.out.println("Testing decrypt: FAILURE");
			fileWriter.write("Testing decrypt: FAILURE\n");
		}
		
		return errNo;
	}
	
	private int testDecryptBig() throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("\nTesting decrypt with a big file ...");
		fileWriter.write("\nTesting decrypt with a big file ...\n");

		int errNo = 5;
		
		System.out.println("Testing decrypt with a big file: sending <d>");
		fileWriter.write("Testing decrypt with a big file: sending <d>\n");
		sendCommand("d");

		if (checkString("enter")) {
			System.out.println("Testing decrypt with a big file: SUCCESS");
			fileWriter.write("Testing decrypt with a big file: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing decrypt with a big file: FAILURE");
			fileWriter.write("Testing decrypt with a big file: FAILURE\n");
		}
		System.out.println("Testing decrypt with a big file: sending <" + outBigFilename + ">");
		fileWriter.write("Testing decrypt with a big file: sending <" + outBigFilename + ">\n");
		sendCommand(outBigFilename);

		if (checkString("enter")) {
			System.out.println("Testing decrypt with a big file: SUCCESS");
			fileWriter.write("Testing decrypt with a big file: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing decrypt with a big file: FAILURE");
			fileWriter.write("Testing decrypt with a big file: FAILURE\n");
		}

		System.out.println("Testing decrypt with a big file: sending <" + deoutBigFilename + ">");
		fileWriter.write("Testing decrypt with a big file: sending <" + deoutBigFilename + ">\n");
		sendCommand(deoutBigFilename);

		process.waitFor(1, TimeUnit.SECONDS);
		//process.waitFor();
		
		if (compareFilesFull(deoutBigFilename, predecBigFilename)) {
			System.out.println("Testing decrypt with a big file: SUCCESS");
			fileWriter.write("Testing decrypt with a big file: SUCCESS\n");
			errNo--;
		} 
		else if (compareFilesSample(deoutBigFilename, predecBigFilename, 0.1)) {
			System.out.println("Testing decrypt with a big file 10%: ALMOST SUCCESS");
			fileWriter.write("Testing decrypt with a big file 10%: ALMOST SUCCESS\n");
			errNo--;
		}
		else if (compareFilesSample(deoutBigFilename, predecBigFilename, 0.5)) {
			System.out.println("Testing decrypt with a big file 50%: HALF SUCCESS");
			fileWriter.write("Testing decrypt with a big file 50%: HALF SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing decrypt with a big file: FAILURE");
			fileWriter.write("Testing decrypt with a big file: FAILURE\n");
		}
		
		return errNo;
	}

	private int testDecryptWithNoFiles()
			throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("\nTesting decrypt with non-existing files ...");
		fileWriter.write("\nTesting decrypt with non-existing files ...\n");

		int errNo = 2;
		
		System.out.println("Testing decrypt with non-existing files: sending <e>");
		fileWriter.write("Testing decrypt with non-existing files: sending <e>\n");
		sendCommand("d");

		if (checkString("enter")) {
			System.out.println("Testing decrypt with non-existing files: SUCCESS");
			fileWriter.write("Testing decrypt with non-existing files: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing decrypt with non-existing files: FAILURE");
			fileWriter.write("Testing decrypt with non-existing files: FAILURE\n");
		}
		
		System.out.println("Testing decrypt with non-existing files: sending <" + wrongFilename + ">");
		fileWriter.write("Testing decrypt with non-existing files: sending <" + wrongFilename + ">\n");
		sendCommand(wrongFilename);

		if (checkString("cannot")) {
			System.out.println("Testing decrypt with non-existing files: SUCCESS");
			fileWriter.write("Testing decrypt with non-existing files: SUCCESS\n");
			errNo--;
		}
		else {
			System.out.println("Testing decrypt with non-existing files: FAILURE");
			fileWriter.write("Testing decrypt with non-existing files: FAILURE\n");
		}

		return errNo;
	}

	private int testUnrecognized() throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("\nTesting unrecognized ...");
		fileWriter.write("\nTesting unrecognized ...\n");

		int errNo = 1;
		
		Random rand = new Random();

		String listOfUnrecChars = "abcfghijklmnoprstuvwxyz1234567890ABCFGHIJKLMNOPRSTUVWXYZ";

		String command = "";
		command += listOfUnrecChars.charAt(rand.nextInt(listOfUnrecChars.length()));

		System.out.println("Testing unrecognized: sending <" + command + ">");
		fileWriter.write("Testing unrecognized: sending <" + command + ">\n");
		sendCommand(command);

		if (checkString("unrecognized")) {
			System.out.println("Testing unrecognized: SUCCESS");
			fileWriter.write("Testing unrecognized: SUCCESS\n");
			errNo--;
		} else {
			System.out.println("Testing unrecognized: FAILURE");
			fileWriter.write("Testing unrecognized: FAILURE\n");
		}
		
		return errNo;
	}

	private boolean compareFilesFull(String filename1, String filename2) throws IOException {
		System.out.println("	Comparing two files: { " + filename1 + ", " + filename2 + " }");
		fileWriter.write("	Comparing two files: { " + filename1 + ", " + filename2 + " }\n");
		try {
			BufferedReader br1 = new BufferedReader(new FileReader(filename1));
			BufferedReader br2 = new BufferedReader(new FileReader(filename2));
			
			int c1, c2;
			while (br1.ready() && br2.ready()) {
				c1 = br1.read();
				c2 = br2.read();
				if (c1 != c2) {
					br1.close();
					br2.close();
					return false;
				}
			}

			if (br1.ready() || br2.ready()) {
				br1.close();
				br2.close();
				return false;
			}

			br1.close();
			br2.close();
			return true;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			System.out.println("	Comparing two files: could not open files");
			fileWriter.write("	Comparing two files: could not open files\n");
			return false;
		}
	}
	
	private boolean compareFilesSample(String filename1, String filename2, double percentage) throws IOException {
		System.out.println("	Comparing two files: { " + filename1 + ", " + filename2 + " }");
		fileWriter.write("	Comparing two files: { " + filename1 + ", " + filename2 + " }\n");
		try {
			BufferedReader br1 = new BufferedReader(new FileReader(filename1));
			BufferedReader br2 = new BufferedReader(new FileReader(filename2));
			
			int numberOfDiff = 0;
			int numberOfChars = 0;
			
			int c1, c2;
			while (br1.ready() && br2.ready()) {
				c1 = br1.read();
				c2 = br2.read();
				if (c1 != c2) {
					numberOfDiff++;
				}
				numberOfChars++;
			}


			while (br1.ready()) {
				c1 = br1.read();
				numberOfDiff++;
				numberOfChars++;
			}
			
			while (br2.ready()) {
				c2 = br2.read();
				numberOfDiff++;
				numberOfChars++;
			}
			
			br1.close();
			br2.close();
			
			if((double)numberOfDiff/numberOfChars < percentage) 
				return true;
			else 
				return true;
		} catch (IOException e) {
			// TODO Auto-generated catch block
			System.out.println("	Comparing two files: could not open files");
			fileWriter.write("	Comparing two files: could not open files\n");
			return false;
		}
	}
	
	private boolean checkString(String str)
			throws IOException, InterruptedException, TimeoutException, ExecutionException {
		System.out.println("	Checking string: { " + str + " }");
		fileWriter.write("	Checking string: { " + str + " }\n");

//		int outAvailable = stdout.available();
//		if (outAvailable > 0) {
//			while(true) {
//				int n = stdout.read(buffer, 0, Math.min(outAvailable, buffer.length));
//				if (n < 2) continue;
//				String outputText = new String(buffer, 0, n);
//				System.out.println("==> " + outputText);
//				if (isFoundCaseInsensitive(outputText, str)) {
//					System.out.println("Checking: " + "SUCCESS");
//					return true;
//				} else {
//					System.out.println("Checking: " + "FAILURE");
//					return false;
//				}
//			}
//		} else {
//			System.out.println("Failed.");
//		}
		
		String line;
		line = timeLimiter.callWithTimeout(() -> bufferedReader.readLine(), 2, TimeUnit.SECONDS);
		System.out.println("	==> " + line);
		fileWriter.write("	==> " + line + "\n");
		if (isFoundCaseInsensitive(line, str)) {
			System.out.println("	Checking string: " + "SUCCESS");
			fileWriter.write("	Checking string: " + "SUCCESS\n");
			return true;
		} else {
			System.out.println("	Checking string: " + "FAILURE");
			fileWriter.write("	Checking string: " + "FAILURE\n");
			return false;
		}

	}

	private String returnString() throws IOException, TimeoutException, InterruptedException, ExecutionException {
		String line = "";
		line = timeLimiter.callWithTimeout(() -> bufferedReader.readLine(), 3, TimeUnit.SECONDS);
		System.out.println("	==> " + line);
		fileWriter.write("	==> " + line + "\n");
		return line;
	}

	private void sendCommand(String cmd) throws IOException {

//		byte[] byteCmd = cmd.getBytes("UTF-8");
//		stdin.write(byteCmd, 0, byteCmd.length);

		bufferedWriter.write(cmd + "\n");
		bufferedWriter.flush();
	}

	private void destroyFiles() throws InterruptedException, IOException {
		String currentDirName = System.getProperty("user.dir");

		Files.deleteIfExists(Paths.get(currentDirName + "\\out.txt"));
		Files.deleteIfExists(Paths.get(currentDirName + "\\deout.txt"));	
		//Files.deleteIfExists(Paths.get(currentDirName + "\\a.exe"));

		System.out.println("Deleting files: SUCCESS");
		fileWriter.write("Deleting files: SUCCESS\n");
	}

}
