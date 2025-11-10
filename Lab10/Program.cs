using System;
using System.Collections.Generic;
using System.Threading;

class Program{
    static Barrier barrier;
    static readonly Mutex fileMutex = new();
    static readonly List<string> results = new();
    static readonly Random rnd = new();

    static readonly string[] phaseNames ={
        "Перевірка доступності баз даних",
        "Виконання запитів",
        "Обробка і збереження результатів"
    };

    static void Main(){
        RunBarrier();
    }

    private static void RunBarrier(){
    }

    static void DatabaseTask(int id){
    }
    // ---------------- CountdownEvent ----------------
    static void CountdownExample(){
    }

    private static void CountdownWork(int id, CountdownEvent countdown){
    }

    // ---------------- ManualResetEvent ----------------
    static void ManualResetExample(){
    }

    // ---------------- AutoResetEvent ----------------
    static void AutoResetExample(){
    }
}