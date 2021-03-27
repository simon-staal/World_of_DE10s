using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;


public class Ipandportscript : MonoBehaviour
{
    [SerializeField] TMP_InputField ipaddress;
    [SerializeField] TMP_InputField port;


    public string ip = "52.56.78.234";
    public string po = "6969";
    // Start is called before the first frame update
    void Start()
    {
        
    }
    private void Awake()
    {
        DontDestroyOnLoad(this.gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        if (ipaddress != null)
        {
            if (ipaddress.text != ip)
            {
                ip = ipaddress.text;
            }
        }
        if (port != null)
        {
            if (port.text != po)
            {
                po = port.text;
            }
        }

    }
}
