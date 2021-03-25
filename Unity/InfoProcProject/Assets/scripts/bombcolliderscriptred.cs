using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bombcolliderscriptred : MonoBehaviour
{
    SpriteRenderer sprite;
    public float timer = 0f;
    [SerializeField] characterController red;
    // Start is called before the first frame update
    void Start()
    {
        sprite = GetComponent<SpriteRenderer>();
    }

    private void Update()
    {
        if (timer > 0)
        {
            timer -= Time.deltaTime;
        }
        if (timer <= 0)
        {
            timer = 0f;
            sprite.color = Color.white;
            red.bombed = false;
        }
    }
    // Update is called once per frame
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("bomb"))
        {
            sprite.color = Color.black;
            timer = 4f;
            red.bombed = true;
        }
    }

}
