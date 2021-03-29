using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class time : MonoBehaviour
{
    [SerializeField] runnerCharacterController tank1;
    [SerializeField] characterController tank2;
    [SerializeField] Score scorecount1;
    [SerializeField] Score scorecount2;
    [SerializeField] bullet shot;
    [SerializeField] bullet shot2;
    [SerializeField] starttimer resetgame;
    int score1 = 0;
    int score2 = 0;
    float timer = 3f;
    public bool redwins = false;
    public bool greenwins = false;
    [SerializeField] client clientscript;
    // Start is called before the first frame update
    void Start()
    {
        scorecount1.outputter = "" + score1;
        scorecount2.outputter = "" + score2;
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        resetgame.gameObject.SetActive(true);
        if (collision.gameObject.CompareTag("runner"))
        {
            score1++;
            scorecount1.outputter = "" + score1;
            GameObject[] objects = GameObject.FindGameObjectsWithTag("bulletred");
            GameObject[] objects1 = GameObject.FindGameObjectsWithTag("bulletblue");
            GameObject[] objects2 = GameObject.FindGameObjectsWithTag("bomb");
            for (int i = 0; i < objects.Length; i++)
            {
                Destroy(objects[i]);
            }
            for (int i = 0; i < objects1.Length; i++)
            {
                Destroy(objects1[i]);
            }
            for (int i = 0; i < objects2.Length; i++)
            {
                Destroy(objects2[i]);
            }
            
        }
        if (collision.gameObject.CompareTag("chaser"))
        {
            score2++;
            scorecount2.outputter = "" + score2;
            GameObject[] objects = GameObject.FindGameObjectsWithTag("bulletred");
            GameObject[] objects1 = GameObject.FindGameObjectsWithTag("bulletblue");
            GameObject[] objects2 = GameObject.FindGameObjectsWithTag("bomb");
            for (int i = 0; i < objects.Length; i++)
            {
                Destroy(objects[i]);
            }
            for (int i = 0; i < objects1.Length; i++)
            {
                Destroy(objects1[i]);
            }
            for (int i = 0; i < objects2.Length; i++)
            {
                Destroy(objects2[i]);
            }
            
        }
    }
    // Update is called once per frame
    private void Update()
    {
        if(score1 == 10)
        {
            redwins = true;
            score1 = 0;
            score2 = 0;
            scorecount2.outputter = "" + score2;
            scorecount1.outputter = "" + score1;
        }
        else if(score2 == 10)
        {
            greenwins = true;
            score2 = 0;
            score1 = 0;
            scorecount2.outputter = "" + score2;
            scorecount1.outputter = "" + score1;
        }
        while(timer > 0)
        {
            timer -= Time.deltaTime;
        }
    }
}
