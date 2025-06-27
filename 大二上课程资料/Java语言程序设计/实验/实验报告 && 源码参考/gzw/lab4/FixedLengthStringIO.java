import java.io.*;

public class FixedLengthStringIO {
  /** Read fixed number of characters from a DataInput stream */
  public static String readFixedLengthString(int size,
      DataInput in) throws IOException {
    // Declare an array of characters
    char[] chars = new char[size];

    // Read fixed number of characters to the array
    for (int i = 0; i < size; i++)
      chars[i] = in.readChar();

    return new String(chars);
  }

  /** Write fixed number of characters to a DataOutput stream */
  public static void writeFixedLengthString(String s, int size,
      DataOutput out) throws IOException {
    char[] chars = new char[size];

    // Fill in string with characters
    s.getChars(0, Math.min(s.length(), size), chars, 0);

    // Fill in blank characters in the rest of the array
    for (int i = Math.min(s.length(), size); i < chars.length; i++)
      chars[i] = ' ';

    // Create and write a new string padded with blank characters
    out.writeChars(new String(chars));
  }
}

