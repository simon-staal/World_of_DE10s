using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Score : MonoBehaviour
{
    public Text myText;
    int i = 20;
    // Start is called before the first frame update
    public string outputter;
    void Start()
    {
        myText = GetComponent<Text>();
        myText.text = "";
    }

    // Update is called once per frame
    void Update()
    {
        myText.text = outputter;
    }
}
