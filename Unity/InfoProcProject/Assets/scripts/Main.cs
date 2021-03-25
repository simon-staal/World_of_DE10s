using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class Main : MonoBehaviour
{
    [SerializeField] Transform runner;
    [SerializeField] Transform chaser;
    int counter = 0;
    void CreateText()
    {
        //Path of the file
        string path = Application.dataPath + "/Log.txt";
        //Create File if it doesnt exist
        if (!File.Exists(path))
        {
            File.WriteAllText(path, "testing this right now \n");
        }
        //Content of file
        string content = "runner position:" + runner.position + "\n";
        string content2 = "chaser position:" + chaser.position + "\n";
        //Text
        File.AppendAllText(path, content);
        File.AppendAllText(path, content2);
    }
    // Start is called before the first frame update
    // Update is called once per frame
    void Update()
    {
        if (counter == 60)
        {
            CreateText();
            counter = 0;
        }
        counter += 1;
    }
}
