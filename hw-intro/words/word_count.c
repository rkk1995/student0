/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utilities */

char *new_string(char *str) {
  char *new_str = (char *)malloc(strlen(str) + 1);
  if (new_str == NULL) {
    return NULL;
  }
  return strcpy(new_str, str);
}

void init_words(WordCount **wclist) {
  /* Initialize word count.
     Returns 0 if no errors are encountered
     in the body of this function; 1 otherwise.
  */
  *wclist = (WordCount *)malloc(sizeof(WordCount));
  if (*wclist == NULL) {
    return ;
  }
  (*wclist)->count = 0;
  (*wclist)->word = NULL;
  (*wclist)->next = NULL;
}

ssize_t len_words(WordCount *wchead) {
  /* Return -1 if any errors are
     encountered in the body of
     this function.
  */
  size_t len = 0;
  for (; wchead; wchead = wchead->next) {
    len = len + (wchead->next == NULL ? 0 : 1);
  }
  return len;
}

WordCount *find_word(WordCount *wchead, char *word) {
  /* Return count for word, if it exists */
  WordCount *wc = NULL;
  for (; wchead; wchead = wchead->next) {
    if (wchead->word == NULL) {
      return NULL;
    }
    if (strcmp(wchead->word, word) == 0) {
      wc = wchead;
      break;
    }
  }
  return wc;
}

int add_word(WordCount **wclist, char *word) {
  /* If word is present in word_counts list, increment the count.
     Otherwise insert with count 1.
     Returns 0 if no errors are encountered in the body of this function; 1
     otherwise.
  */
  WordCount *new_word, *found_word = find_word(*wclist, word);

  if (found_word == NULL) {
    if ((*wclist)->word == NULL) {
      new_word = *wclist;
    } else {
      init_words(&new_word);
      new_word->next = *wclist;
      *wclist = new_word;
    }


    new_word->word = new_string(word);
    new_word->count = 1;
    printf("%s, %d\n", word, new_word->count);
  } else {
    found_word->count += 1;
  }
  return 0;
}

void print_node(WordCount *wchead) {
  if (wchead == NULL) {
    printf("NULL\n");
  }
  printf("%i\t%s\n", wchead->count, wchead->word);

}

void fprint_words(WordCount *wchead, FILE *ofile) {
  /* print word counts to a file */
  WordCount *wc;
  for (wc = wchead; wc->word != NULL; wc = wc->next) {
    fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
  }
}
