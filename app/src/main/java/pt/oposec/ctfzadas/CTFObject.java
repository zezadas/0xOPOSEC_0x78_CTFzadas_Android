package pt.oposec.ctfzadas;

import android.util.Log;
import android.webkit.JavascriptInterface;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

public class CTFObject {

    public native String firstFlag();

    public native String secondFlag(String key);

    public native String thirdFlag(byte[] payload);

    @JavascriptInterface
    public String um() {
        return firstFlag();
    }

    @JavascriptInterface
    public String dois(String five_numbers) {
        Log.d("OPOSEC", "Pin have 5 numbers (String)\nString starts with \"{oposec}\"");
        Log.d(secondFlag(five_numbers), secondFlag(five_numbers));
        return secondFlag(five_numbers);
    }

    public static byte[] hexStringToByteArray(String s) {
        int len = s.length();
        byte[] data = new byte[(len / 2)+1];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i+1), 16));
        }
        Integer x=0;
        data[data.length-1]=x.byteValue();
        return data;
    }

    @JavascriptInterface
    public String tres(String payload) {
        Log.d("aaa-", payload);
        byte[] hexArray = hexStringToByteArray(payload);
        Log.d("aaa:", String.valueOf(hexArray));
        return thirdFlag(hexArray);
    }

    @JavascriptInterface
    public String getProcSelfMaps() {
        String output = "";
        try {
            Set<String> libs = new HashSet<String>();
            String mapsFile = "/proc/" + android.os.Process.myPid() + "/maps";
            BufferedReader reader = new BufferedReader(new
                    FileReader(mapsFile));
            String line;
            while ((line = reader.readLine()) != null) {
                if (line.endsWith(".so")) {
                    //int n = line.lastIndexOf(" ");
                    //libs.add(line.substring(n + 1)+"\n");
                    libs.add(line + "\n");
                }
            }
            //Log.d("Ldd", libs.size() + " libraries:");
            for (String lib : libs) {
                output += lib;
                //Log.d("Ldd", lib);
            }
            return output;
        } catch (FileNotFoundException e) {
            // Do some error handling...
        } catch (IOException e) {
            // Do some error handling...
        }

        return "";
    }

}
