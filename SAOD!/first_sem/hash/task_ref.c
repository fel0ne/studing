#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int hash(char c, int size) {
    return (c % size + size) % size; 
}

int countUniqueChars(const char* str) {
    bool seen[256] = {false};
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (!seen[c]) {
            seen[c] = true;
            count++;
        }
    }
    return count;
}

int linearProbe(int *table, int size, int key, int *probes) {
    int m = 0;
    int index;
    do {
        index = (key + m) % size;
        if (table[index] == 0) {
            *probes = m;
            return index;
        }
        m++;
    } while (m < size);
    *probes = -1; 
    return -1;
}

int quadraticProbe(int *table, int size, int key, int *probes) {
    int m = 0;
    int index;
    do {
        index = (key + m * m) % size;
        if (table[index] == 0) {
            *probes = m;
            return index;
        }
        m++;
    } while (m < size);
    *probes = -1; 
    return -1;
}

int insert(int *table, int size, char c, int method) {
    int key = hash(c, size);
    for (int i = 0; i < size; i++) {
        int probeIndex;
        if (method == 1) {
            probeIndex = (key + i) % size;
        } else {
            probeIndex = (key + i * i) % size;
        }
        if (table[probeIndex] == 0) {
            break; 
        }
        if (table[probeIndex] == (int)c) {
            return 0; 
        }
    }
    // Insert
    int probes;
    int index;
    if (method == 1) {
        index = linearProbe(table, size, key, &probes);
    } else {
        index = quadraticProbe(table, size, key, &probes);
    }
    if (index == -1) {
        return -1; 
    }
    table[index] = (int)c;
    return probes; 
}

void printHashTable(int *table, int size, const char *method) {
    printf("%s хеш-таблица:\n", method);
    for (int i = 0; i < size; i++) {
        if (table[i] == 0) {
            printf("- "); 
        } else {
            printf("%c ", table[i]); 
        }
    }
    printf("\n\n");
}

int main() {
    char key[] = "The integration of digital technology into education has revolutionized how knowledge is acquired, shared, and applied in the 21st century. From interactive e-learning platforms to AI-driven tutoring systems, technology has dismantled traditional barriers, making education more accessible, personalized, and efficient. This transformation has not only reshaped classrooms but also redefined the roles of educators and learners, creating a dynamic ecosystem where innovation thrives.One of the most significant advancements is the rise of Massive Open Online Courses (MOOCs). Platforms like Coursera, edX, and Khan Academy offer courses from top universities to anyone with an internet connection, democratizing access to high-quality education. Learners in remote areas, working professionals, and those with financial constraints can now study subjects ranging from quantum physics to graphic design at their own pace. This shift has challenged the notion that education must be confined to physical institutions, fostering a global community of self-directed learners.Moreover, artificial intelligence (AI) has introduced tools that adapt to individual learning styles. Adaptive learning software analyzes student performance in real time, identifying strengths and weaknesses to tailor content accordingly. For instance, language apps like Duolingo use AI to adjust difficulty levels based on user progress, ensuring optimal engagement. Similarly, virtual tutors powered by natural language processing (NLP) provide instant feedback, reducing dependency on human instructors for routine queries. These innovations not only enhance comprehension but also free educators to focus on mentorship and critical thinking exercises.The COVID-19 pandemic accelerated the adoption of hybrid learning models, blending online and in-person instruction. Video conferencing tools like Zoom and Microsoft Teams became lifelines for schools and universities, enabling continuity amid lockdowns. While this transition exposed disparities in digital access—highlighting the “homework gap” faced by low-income students—it also spurred initiatives to distribute devices and improve internet connectivity. Governments and nonprofits worldwide recognized that equitable access to technology is no longer a luxury but a necessity for educational equity.Another transformative trend is the use of virtual and augmented reality (VR/AR) in classrooms. Immersive simulations allow students to explore historical sites, conduct virtual lab experiments, or visualize complex mathematical concepts. For example, medical students can practice surgeries in risk-free VR environments, while history classes might “visit” ancient civilizations through AR-enhanced textbooks. Such experiential learning boosts retention and engagement, catering to diverse learning preferences.However, the digital revolution also presents challenges. Concerns about data privacy, screen time, and the erosion of face-to-face interaction persist. Critics argue that over-reliance on technology may diminish soft skills like teamwork and empathy, which are cultivated through in-person collaboration. Additionally, the rapid pace of technological change demands constant upskilling from educators, many of whom struggle to keep up with new tools. Addressing these issues requires a balanced approach—embracing technology while preserving the human elements of teaching.Looking ahead, emerging technologies like blockchain could further disrupt education. Blockchain-based credentialing systems might replace traditional diplomas, enabling secure, verifiable records of lifelong learning. Similarly, decentralized platforms could empower learners to curate personalized education pathways, combining courses from multiple institutions. As the gig economy grows, such flexibility will be crucial for workers navigating career shifts in an automated world.In conclusion, digital technology has irreversibly altered the educational landscape, offering unprecedented opportunities and challenges. Its success hinges on inclusive policies, ethical frameworks, and collaboration between tech developers, educators, and policymakers. By harnessing innovation responsibly, society can ensure that education remains a catalyst for empowerment, equality, and global progress in the digital age.";
    int numKeys = countUniqueChars(key);

    int size = 47;
    int *linearTable = (int *)calloc(size, sizeof(int));
    int *quadraticTable = (int *)calloc(size, sizeof(int));

    if (linearTable == NULL || quadraticTable == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 1;
    }

    int linearCollisions = 0;
    int quadraticCollisions = 0;
    for (int j = 0; j < strlen(key); j++) {
        int lin_result = insert(linearTable, size, key[j], 1);
        int quad_result = insert(quadraticTable, size, key[j], 2);
        if (lin_result >= 0) linearCollisions += lin_result;
        if (quad_result >= 0) quadraticCollisions += quad_result;
    }

    printHashTable(linearTable, size, "Линейная");
    printHashTable(quadraticTable, size, "Квадратичная");

    printf("| %-15s | %-19s | %-19s | %-19s |\n", "Размер", "Количество исх. символов", "Кол-во коллизий (Линейные пробы)", "Кол-во коллизий (Квадратичные пробы)");
    printf("|-----------------|---------------------|-------------------------|-------------------------|\n");

    free(linearTable);
    free(quadraticTable);

    for (int size = 11; size <= 101; size++) {
        if (!isPrime(size)) continue;

        int *linearTable = (int *)calloc(size, sizeof(int));
        int *quadraticTable = (int *)calloc(size, sizeof(int));

        if (linearTable == NULL || quadraticTable == NULL) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            return 1;
        }

        int linearCollisions = 0;
        int quadraticCollisions = 0;

        for (int j = 0; j < strlen(key); j++) {
            int lin_result = insert(linearTable, size, key[j], 1);
            int quad_result = insert(quadraticTable, size, key[j], 2);
            if (lin_result >= 0) linearCollisions += lin_result;
            if (quad_result >= 0) quadraticCollisions += quad_result;
        }

        printf("| %-15d | %-19d | %-23d | %-23d |\n", size, numKeys, linearCollisions, quadraticCollisions);

        free(linearTable);
        free(quadraticTable);
    }

    return 0;
}