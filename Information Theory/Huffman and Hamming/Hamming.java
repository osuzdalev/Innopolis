
import java.util.Arrays;
import java.util.HashMap;
import java.util.Random;

import static java.lang.Math.pow;


public class Hamming implements MessengerClassLib.lib.IAlgorithm{

    /* If binaryInput is false, all byte number will be converted into binary */
    boolean asciiInput;

    public byte[] alg_input;

    /*  Hamming(4,7) is implemented, so SizeOfWord = 4, SizeOfEncodedWord = 7
     *  NumberOfProtectionBits = 3 */
    private static final int SizeOfWord = 4;
    private static final int SizeOfEncodedWord = 7;
    private static final int NumberOfProtectionBits = 3;

    /* if element of list is 1, bit with the same index
     * is summed to create protection bit */
    private static final byte[] FirstBitSum = { 1, 1, 0, 1 };
    private static final byte[] SecondBitSum = { 1, 0, 1, 1 };
    private static final byte[] ThirdBitSum = { 0, 1, 1, 1 };


    private byte[][] checkMatrixTrans = new byte[SizeOfEncodedWord][NumberOfProtectionBits];
    private byte[][] generatorMatrix = new byte[SizeOfWord][SizeOfEncodedWord];

    /* Constructor */
    public Hamming(){ }

    /* Member gets array of bytes as an input and returns encoded message as array of bytes */
    public byte[] encode(byte[] in) {

        alg_input = AsciiToBinary(in);

        byte[] encodedMessage = new byte[alg_input.length/SizeOfWord*8];
        byte[] word;
        byte[] encodedWord;
        for (int i = 0; i < alg_input.length / SizeOfWord; i += 1) {
        /* In loop 4 bits are given to createEncodedWord member to create codeword */
            word = Arrays.copyOfRange(alg_input, SizeOfWord*i, SizeOfWord*i + SizeOfWord);
            encodedWord = createEncodedWord(word);
            encodedMessage[0 + i*8] = 0;
            encodedMessage[1 + i*8] = encodedWord[0];
            encodedMessage[2 + i*8] = encodedWord[1];
            encodedMessage[3 + i*8] = encodedWord[2];
            encodedMessage[4 + i*8] = encodedWord[3];
            encodedMessage[5 + i*8] = encodedWord[4];
            encodedMessage[6 + i*8] = encodedWord[5];
            encodedMessage[7 + i*8] = encodedWord[6];
        }

        return binaryToAscii(encodedMessage);
    }


    /* Member returns encoded Word */
    private byte[] createEncodedWord(byte[] word ){

        byte p1 = 0, p2 = 0, p3 = 0;
        byte[] enWord = new byte[SizeOfEncodedWord];
        p1 = (byte) ((word[0] + word[1] + word[3])%2);
        p2 = (byte) ((word[0] + word[2] + word[3])%2);
        p1 = (byte) ((word[1] + word[2] + word[3])%2);

        enWord[0] = p1;
        enWord[1] = p2;
        enWord[2] = word[0];
        enWord[3] = p3;
        enWord[4] = word[1];
        enWord[5] = word[2];
        enWord[6] = word[3];

        return enWord;
    }

    /* Member gets encoded Message as an argument */
    public byte[] decode(byte[] encodedMessage, Object r){

        encodedMessage = AsciiToBinary(encodedMessage);
        int numberOfWords = encodedMessage.length / 8 / 2;


        byte[] decodedMessage = new byte[numberOfWords];
        byte[] word1, word2;

        int j = 0;

        for (int i = 0; i < encodedMessage.length / 8; i += 2) {
            word1 = Arrays.copyOfRange(encodedMessage, i * 8 + 1, (i + 1) * 8);
            word2 = Arrays.copyOfRange(encodedMessage, (i+1) * 8 + 1, (i+2) * 8);
            /* decodeWord function gets an encodedWord as an argument and returns decodedWord */
            decodedMessage[j] = decodeWord(word1, word2);
            j++;
        }
        return decodedMessage;
    }

    /* Method gets encoded word and returns decoded Word
     * If in word only one error, it will be corrected */
    private byte decodeWord( byte[] word1, byte[] word2){
        boolean errorDetected = false;
        int[] sympthom = new int[NumberOfProtectionBits];
        int value;
        /* calculating of a symptons for an encoded word1
         * by multiplying encoded word1 on Transponed checking Matrix */
        for ( int j = 0; j < NumberOfProtectionBits; j++){
            value = 0;
            for ( int i = 0; i < SizeOfEncodedWord; i++){
                value += word1[i]*checkMatrixTrans[i][j];
            }
            if ( value%2 != 0 ) { errorDetected = true; }
            sympthom[j] = value%2;
        }


        if (sympthom[0] != 0 || sympthom[1] != 0 || sympthom[2] != 0 ){
            errorDetected = true;
        }

        if ( errorDetected ){
            /* error Position can be calculated via converting sympthom form binary to decimal */
            int errorPos = getErrorPos( sympthom );
            /* if error position less or equal than 7 and bigger or equal than 0, error can be corrected */
            if ( errorPos >= 0 || errorPos <= 7 ){
                if (word1[errorPos - 1] == 1) {
                    word1[errorPos - 1] = 0;
                } else {
                    word1[errorPos - 1] = 1;
                }
            }
        }


        for ( int j = 0; j < NumberOfProtectionBits; j++){
            value = 0;
            for ( int i = 0; i < SizeOfEncodedWord; i++){
                value += word2[i]*checkMatrixTrans[i][j];
            }
            if ( value%2 != 0 ) { errorDetected = true; }
            sympthom[j] = value%2;
        }


        if (sympthom[0] != 0 || sympthom[1] != 0 || sympthom[2] != 0 ){
            errorDetected = true;
        }

        if ( errorDetected ){
            /* error Position can be calculated via converting sympthom form binary to decimal */
            int errorPos = getErrorPos( sympthom );
            /* if error position less or equal than 7 and bigger or equal than 0, error can be corrected */
            if ( errorPos >= 0 || errorPos <= 7 ){
                if (word2[errorPos - 1] == 1) {
                    word2[errorPos - 1] = 0;
                } else {
                    word2[errorPos - 1] = 1;
                }
            }
        }

        sympthom = null;

        byte initialWord = 0;
        initialWord += (byte)(word1[2] * pow(2, 7));
        initialWord += (byte)(word1[4] * pow(2, 6));
        initialWord += (byte)(word1[5] * pow(2, 5));
        initialWord += (byte)(word1[6] * pow(2, 4));
        initialWord += (byte)(word2[2] * pow(2, 3));
        initialWord += (byte)(word2[4] * pow(2, 2));
        initialWord += (byte)(word2[5] * pow(2, 1));
        initialWord += (byte)(word2[6] * pow(2, 0));

        return initialWord;
    }

    /* member gets number in binary and returns in decimal */
    private int getErrorPos(int[] binNumber){

        int decPos = 0;
        for (int i = 0; i < NumberOfProtectionBits; i++){
            decPos += binNumber[i] * pow(2, i);
        }
        return decPos;
    }

    /* Method make String from byte Array */
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

    /* Method make byte Array from String */
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

    /* Method returns bits sequence of input in ASCII code
     * (Represents all ascii codes in binary) */
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

    /* Method returns Array of ASCII codes from bits sequence */
    private byte[] binaryToAscii(byte[] bin){

        int l = bin.length / 8;
        if ( bin.length%8 != 0){
            l = bin.length / 8 + 1;
        }
        int k = 8;
        byte[] res = new byte[l];

        for (int i = 0; i < bin.length; i+=k){
            if ( i + k > bin.length ) { k = bin.length - i; }
            String word = "";
            for ( int j = i; j < i+k; j++ ){
                word += Byte.toString(bin[j]);
            }
            res[i/8] = (byte)(Integer.parseInt(word, 2));

        }

        return res;
    }

    public Object getDictionary(){
        return null;
    }

}

