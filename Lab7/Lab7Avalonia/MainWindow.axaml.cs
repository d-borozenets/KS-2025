using System;
using System.Diagnostics;
using System.Globalization;
using Avalonia.Controls;
using System.IO;
using System.Linq;
using System.Threading.Tasks;

namespace Lab7AvaloniaSync;

public partial class MainWindow : Window{
    private readonly Random random = new();

    public MainWindow(){
        InitializeComponent();
    }

    // === Sync кнопка ===
    private void OnSyncClick(object? sender, Avalonia.Interactivity.RoutedEventArgs e){
        Status.Text = "Обробка Sync...";
        
        Status.Text = $"Готово! (Sync)   мс";
    }

    // === Async кнопка ===
    private async void OnAsyncClick(object? sender, Avalonia.Interactivity.RoutedEventArgs e){
        Status.Text = "Обробка Async...";
        
        Status.Text = $"Готово! (Async)   мс";
    }

    // === Кнопка Тест (для UI responsiveness) ===
    private void OnTestClick(object? sender, Avalonia.Interactivity.RoutedEventArgs e){
        Test.Text = "Тест: " + random.NextInt64();
    }

    // ======================================================
    // ===============  СИНХРОННА ВЕРСІЯ  ==================
    // ======================================================

    private static void ProcessInputFilesSync(int start, int end){
        
    }

    private static void ProcessFileSync(string path){
        
    }

    // ======================================================
    // ===============  АСИНХРОННА ВЕРСІЯ  ==================
    // ======================================================

    private static async Task ProcessInputFilesAsync(int start, int end){
        
    }

    private static async Task ProcessFileAsync(string path){
        
    }

    // ======================================================
    // ===============  ДОПОМІЖНІ МЕТОДИ  ==================
    // ======================================================

    private static double Sum(double[] numbers){
        double sum = 0;
        foreach (var n in numbers)
            sum += n;
        return sum;
    }

    private static double[] TextToArray(string text){
        return text
            .Split(new[]{ ' ', '\r', '\n', '\t' }, StringSplitOptions.RemoveEmptyEntries)
            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
            .ToArray();
    }
}