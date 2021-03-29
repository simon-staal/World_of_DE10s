using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class starttimer : MonoBehaviour
{
    float timer = 4f;
    [SerializeField] TMP_Text text;

    [SerializeField] characterController redtank;
    [SerializeField] runnerCharacterController greentank;
    // Start is called before the first frame update
    void Start()
    {
        text = GetComponent<TMP_Text>();
        
    }

    // Update is called once per frame
    void Update()
    {
        if (timer > 0)
        {
            redtank.isrunning = false;
            greentank.isrunning = false;
            timer -= Time.deltaTime;
            int x = (int)timer;
            text.text = x.ToString();
        }
        else
        {
            text.text = "0";
            redtank.isrunning = true;
            greentank.isrunning = true;
            gameObject.SetActive(false);
            timer = 4f;
        }
    }
}
