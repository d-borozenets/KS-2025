class Program{
    static void Main(){
        var rnd = new Random();
        GenerateFile(rnd, 1);
        GenerateFile(rnd, 2);
        GenerateFile(rnd, 3);
    }

    private static void GenerateFile(Random rnd, int value){
        using var sw = new StreamWriter($"input{value}.txt");
        for (int i = 0; i < 5_000_000; i++) 
            sw.Write($"{rnd.NextDouble() * 100*value:F4} ");
    }
}