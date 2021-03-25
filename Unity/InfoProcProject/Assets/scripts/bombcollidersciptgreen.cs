using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bombcollidersciptgreen : MonoBehaviour
{
    SpriteRenderer sprite;
    public float timer = 0f;
    [SerializeField] runnerCharacterController green;
    // Start is called before the first frame update
    void Start()
    {
        sprite = GetComponent<SpriteRenderer>();
    }

    // Update is called once per frame
    private void Update()
    {
        if (timer > 0)
        {
            timer -= Time.deltaTime;
        }
        if (timer <= 0) {
            timer = 0f;
            sprite.color = Color.white;
            green.bombed = false;
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("bomb"))
        {
            sprite.color = Color.black;
            timer = 4f;
            green.bombed = true;
        }
    }
}
