

import java.util.*;

import static java.util.Arrays.*;


public class Huffman implements MessengerClassLib.lib.IAlgorithm {
    /* SizeOfWord is equal to number of bits reqred to encode one symbol */
    private Integer SizeOfWord;

    private boolean asciiInput;

    /* Nessesary for correct work with text in asci */
    private boolean asci;

    /* dictionary = {word : encodedWord} */
    private HashMap<Byte, String> dictionary = new HashMap<>();

    /* HashMap stores frequencies of character of message { word : freq } */
    private HashMap<Byte, Integer> frequency = new HashMap<>();

    /* Initial message  */
    public byte[] input;

    /* Constructor
     * Gets sizeOfWord as the first argument, array of bytes as second
     * if input is an array of ASCII code, third argument is true, else is false */
    public Huffman(){
        SizeOfWord = 1;
        asciiInput = true;

    }

    /* Member allows to change the amount of bits required on encoding one symbol */

    /* Member returns array of bits of an encoded message */
    public byte[] encode(byte[] in){
        frequency.clear();
        dictionary.clear();


        input = in;

        byte word = input[0];
        for ( int i = 0; i < input.length; i+=SizeOfWord){
            if (i + SizeOfWord <= input.length){
                /* Word is a array of bits of length 'SizeOfWord' */
                word = input[i];
            }

            /* If word already've been added to the frequency HashMap, increase frequency by one */
            if ( frequency.containsKey( word ) ){
                int freq = frequency.get( word );
                frequency.put( word ,freq + 1);
            }
            /* If word is appeared first time, add word to frequency and set it's frequency to 1 */
            else { frequency.put( word, 1); }
        }


        /* Calling member to build a Huffman tree */
        Node root = buildTree(frequency);


        /* Calling member to fill the dictionary */
        buildCode(root, "");

        /* Calling member create encoded message */
        //byte[] code = encode( ByteToString(input) );


        return encodeMessage( input );
    }

    /* Member returns dictionary (I can't really remember why it's like this, but it works) */
    public Object getDictionary(){

        HashMap<String, Byte> decodeDict = new HashMap<String, Byte>();
        for (  Byte key : dictionary.keySet() ){
            decodeDict.put( dictionary.get(key), key  );
        }

        return decodeDict;
    }

    /* Member creates encoded message by substituting initial words by encoded words from dictionary */
    private byte[] encodeMessage(byte[] input){

        String message = "";
        for ( int i = 0; i < input.length; i++) {
            message += dictionary.get(input[i]);
        }
        //dictionary.put("size", Integer.toString(SizeOfWord));
        byte[] encodedMessage = binaryToAscii(message);

        return encodedMessage;
    }

    /* Member gets encodedMessage as first argument and dictionary as second argument
     * Returns decoded message as array of bytes */
    public byte[] decode( byte[] input, Object d ){

        input = AsciiToBinary(input);
        SizeOfWord = 8;
        asciiInput = true;
        HashMap<String, Byte> dict = (HashMap<String, Byte>)d;

        return decodeMessage( input, dict );


    }

    /* Member called from decompress member and decodes the message */
    private byte[] decodeMessage(byte[] encodedMessage, HashMap<String, Byte> dict ){
        String word = "";
        ArrayList<Byte> message = new ArrayList<Byte>();
        for ( int i = 0; i < encodedMessage.length; i++ ){
            word += Byte.toString(encodedMessage[i]);
            if ( dict.containsKey(word) ){
                message.add( dict.get(word) );
                word = "";
            }
        }

        byte[] decodedMes = new byte[ message.size() ];
        int i = 0;
        for (Byte b : message){
            decodedMes[i] = (byte)b;
            i++;
        }

        return decodedMes;
    }

    /* Method returns Array of ASCII codes from bits sequence */
    private byte[] binaryToAscii(String bin){
        int l;
        if ( bin.length()%8 != 0){
            l = bin.length()/8 + 1;
        }
        else {
            l = bin.length()/8;
        }

        byte[] res = new byte[l];
        int k = 8;
        for (int i = 0; i < bin.length(); i+=8){
            String word = "";
            if ( i + k >= bin.length() ) { k = bin.length() - i; }
            for ( int j = i; j < i+k; j++ ){
                word += bin.charAt(j);
            }
            res[i/8] = (byte)(Integer.parseInt(word, 2));
        }

        return res;
    }


    /* Method returns Array of ASCII codes from bits sequence */
    private byte[] binaryToAscii(byte[] bin){

        int l = bin.length / 8;
        if ( bin.length%8 != 0){
            l = bin.length / 8 + 1;
        }
        int k = 8;
        byte[] res = new byte[l];

        for (int i = 0; i < bin.length; i+=k){
            if ( i + k >= bin.length ) { k = 8 - bin.length + i; }
            String word = "";
            for ( int j = i; j < i+k; j++ ){
                word += Byte.toString(bin[j]);
            }
            res[i/8] = (byte)(Integer.parseInt(word, 2));

        }

        return res;
    }


    private byte[] AsciiToBinary(byte[] in){

        byte[] binArr = new byte[in.length*8];
        for (int j = 0; j < in.length; j++)
        {
            int val = in[j];
            for (int i = 0; i < 8; i++) {
                binArr[i + j * 8] = (byte) ((val & 128) == 0 ? 0 : 1);
                val <<= 1;
            }
        }

        return binArr;
    }

    /* Member to cast byte array as a string */
    private String ByteToString(byte[] input){
        String result = "";


        for (int i = 0; i < input.length; i++) {
            if (input[i] == 1) {
                result += "1";
            }
            else {
                result += "0";
            }
        }

        return result;
    }

    /* Member to cast string to a byte array */
    private byte[] StringToByte(String message){
        byte[] byteArray = new byte[message.length()];
        for (int i = 0; i < message.length(); i++) {
            if (message.charAt(i) == '1') {
                byteArray[i] = 1;
            }
            else {
                byteArray[i] = 0;
            }
        }
        return byteArray;
    }


    /* Member building Huffmans tree
    *  As argument gets a frequencies of chars from message  */
    private Node buildTree(Map<Byte, Integer> freq){

        Comparator<Node> comparator = new NodeComparator();
        PriorityQueue<Node> pq = new PriorityQueue<>(comparator);

        /* For each word created node and it's added to the Priority Queue */
        for ( byte key : freq.keySet()){
            Node n = new Node(Byte.toString(key), freq.get(key), null, null);
            pq.add(n);
        }

        /* From two nodes with smallest frequencies created another node and 've been put back to Queue */
        while ( pq.size() != 1 ){
            Node left = pq.poll();
            Node right = pq.poll();
            Node parent = new Node("\0", left.getFreq() + right.getFreq(), left, right);
            pq.add(parent);
        }

        /* Returns root of the tree (last node in Queue) */
        return pq.poll();
    }

    /* Member creates code for each word using Huffman tree
     * Gets root of the tree as first argument, second argument is requared as a code word
     * Each time function is called, 0 or 1 is added to 's' untill leaf is reached, and 's' assigned as a code word for a char in leaf node */
    private void buildCode (Node x, String s){
        /* Untill 'x' node is not a leaf, all member again and add bit ti codeword */
        if ( !x.isLeaf() )
        {
            buildCode(x.left, s+"0");
            buildCode(x.right, s+"1");
        }
        /* if 'x' node is a leaf, add word form node as a key in dictionary and 's' codeword as a value */
        else{
            dictionary.put( Byte.parseByte(x.word) , s );
        }
    }

    /* Comparator class for a priority Queue */
    private class NodeComparator implements Comparator<Node>{
        @Override
        public int compare(Node n1, Node n2){
            /* Returns -1 if frequency of n1 node is less than n2's frequency */
            if ( n1.getFreq() < n2.getFreq() )
            { return -1; }

            /* Returns -1 if frequency of n1 node is bigger than n2's frequency */
            if ( n1.getFreq() > n2.getFreq() )
            { return 1; }

            /* If frequency of n1 node is equal to n2's frequency, return 0 */
            return 0;
        }
    }

    /* Class Node for a Huffman tree */
    private class Node {

        private String word; // word which should be encoded
        private Integer frequency; // frequency of this word
        private Node left, right; // It's offsprings

        /* Constructor for a Node class
         * 'w' is word to encode, 'freq' is frequency of this word, 'l' and 'r' it's offsprings */
        Node( String w, int freq, Node l, Node r ){
            word = w;
            frequency = freq;
            left = l;
            right = r;
        }

        /* Method returns true if node is leaf ( left and right are equal to null)
         * if not, returns false */
        private boolean isLeaf(){
            if (( left == null ) || ( right == null ))
            { return true; }
            return false;
        }

        /* Method returns frequency of a node */
        private int getFreq(){
            return frequency;
        }

    }

}
