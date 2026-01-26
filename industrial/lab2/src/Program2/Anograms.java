package Program2;

import java.util.*;

public class Anograms {

	public static void main(String[] args) {
		
		Scanner in = new Scanner( System.in );
        while ( in.hasNextLine() ) {
            String s = in.nextLine();
            String[] words = s.split("[^\\p{L}]+");
            Set<String> uniquePairs = new HashSet<>();
            int n = words.length;
            for (int i = 0; i < n; i++) {
            	String reversed = new StringBuilder(words[i]).reverse().toString();
            	for (int j = i + 1; j < n; j ++) {
            		if (reversed.equalsIgnoreCase(words[j])) {
            			String pair;
            			if (words[i].compareToIgnoreCase(words[j]) < 0) {
            			    pair = words[i] + " - " + words[j];
            			} else {
            			    pair = words[j] + " - " + words[i];
            			}
            			uniquePairs.add(pair.toLowerCase());
            		}
            	}
            }
            for (String pair : uniquePairs) {
                System.out.println(pair);
            }
        }
        in.close();
	}

}
