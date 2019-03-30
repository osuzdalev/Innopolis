import java.io.File;
        import java.io.FileInputStream;
        import java.io.FileNotFoundException;
        import java.io.IOException;

public class test {
    static public void main(String args[]) throws IOException {
        File f = new File("pic.tif");
        FileInputStream a = new FileInputStream(f);
        byte[] arr = new byte[a.available()];
        a.read(arr, 0, a.available());

        Hamming ham = new Hamming();
    }
}
