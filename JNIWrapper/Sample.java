import java.lang.String;

class Sample {
    private String str = "Java";

    public Sample(){}

    public String StringTest(String s) {
        return "[Class Method] " + s + " " + this.str;
    }

    public static String StringStaticTest(String s) {
        return "[Static Method] " + s + " Java";
    }
}