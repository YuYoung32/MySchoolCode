#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// 原始数据项数
#define DATA_NUM 506
// 训练集占总数比例,剩下的即为测试集,范围(0.0,1.0)
#define TRAIN_DATASET_RATIO 0.7
// 训练轮数
#define EPOCH 200
// 学习率
#define LEARNING_RATE 0.01
// 特征数量(X)数量,在这个数据集里,13个特征,最后一个是平均房价(Y)
#define FEATURE_NUM 13
#define PARA_NUM (FEATURE_NUM+1)
// 初始化的随机数种子,unsigned int, 要想每次随机,使用(unsigned)time(NULL)
#define RAND_SEED 0

typedef struct Dataset {
    // 一维数组,每14个数据为一项
    double *data;
    // 数量
    int amount;
} dataset;

/**
 * 读取文件并创建数据集,去除表头,得到纯数据
 * @param filePath 文件路径
 * @param ratio 训练集占据比例
 * @param train 训练集
 * @param test 数据集
 */
void FileReaderAndSeparation(char filePath[], double ratio, dataset *train, dataset *test);

/**
 * 归一化数据
 * @param dataCnt 数据个数
 * @param data 数据数组
 */
void FlatData(int dataCnt, double data[]);

/**
 * 预测函数 多元一次函数
 * @param cnt 项数
 * @param parameters 系数
 * @param x 自变量
 * @return y 因变量(房价)
 */
double PredictionFunction(int cnt, const double parameters[], const double x[]);

/**
 * 损失函数,得出每轮的损失值
 * @param dataCnt 数据集项数
 * @param prediction 预测值数组
 * @param actuality 真实值数组
 * @return 损失值
 */
double LossFunction(int dataCnt, double prediction[], double actuality[]);

/**
 * 梯度下降法
 * @param learningRate 学习率
 * @param paraCnt 变量数组长度
 * @param parameters 变量数组
 * @param trainDataset 数据集
 * @param prediction 预测值
 * @param actuality 实际值
 * @return
 */
double
GradientDescent(double learningRate, int paraCnt, double parameters[], dataset trainDataset, const double prediction[],
                const double actuality[]);


/**
 * Root Mean Square Error均方根误差计算
 * @param dataCnt 数据项数
 * @param prediction 预测值数组
 * @param actuality 实际值数组
 * @return 误差值
 */
double RMSE(int dataCnt, double prediction[], double actuality[]);

int main() {
    // region 数据集准备 todo:相对路径似乎不行
    char filePath[] = "D:\\CLionFiles\\MySchoolCode\\CProgramExercise\\iMooc\\MultipleLinearRegression\\housing.txt";
    dataset trainDataset;
    dataset testDataset;
    FileReaderAndSeparation(filePath, TRAIN_DATASET_RATIO, &trainDataset, &testDataset);
    // endregion
    // region 参数初始化
    double parameters[PARA_NUM] = {1.0};
    srand(RAND_SEED);
    for (int i = 0; i < PARA_NUM; ++i) {
        parameters[i] = rand() % 1000 / 1000.0;
    }
    // endregion 参数初始化
    // region迭代训练n轮 循环条件也可以判断为loss值不再变化
    double loss;
    for (int i = 1; i <= EPOCH; ++i) {
        // 每次训练对全体进行训练,并不分批
        double actualY[trainDataset.amount];
        double predictY[trainDataset.amount];
        for (int j = 0; j < trainDataset.amount; ++j) {
            actualY[j] = trainDataset.data[(PARA_NUM) * (j + 1) - 1];
            double x[PARA_NUM];
            for (int a = 1; a < PARA_NUM; ++a) {
                x[a] = trainDataset.data[(PARA_NUM) * j + a - 1];
            }
            x[0] = 1.0;
            predictY[j] = PredictionFunction(PARA_NUM, parameters, x);
        }
        if (i == 1) {
            printf("This is %d steps training....\n", i);
            loss = LossFunction(trainDataset.amount, predictY, actualY);
            printf("the original loss is %lf\n\n", loss);
        }
        GradientDescent(LEARNING_RATE, PARA_NUM, parameters, trainDataset, predictY, actualY);
        // 每100次训练打印一次
        if (!(i % (EPOCH / 10))) {
            printf("This is %d steps training....\n", i);
            loss = LossFunction(trainDataset.amount, predictY, actualY);
            printf("the loss is %lf\n\n", loss);
        }
    }
    printf("After training, the loss is %lf\nThe parameters from w0,w1 to w13 (attention: w0 is the bias) are as below:\n",
           loss);
    for (int i = 0; i < PARA_NUM; ++i) {
        printf("%.4lf  ", parameters[i]);
        if (i == PARA_NUM - 1) { printf("\n"); }
    }
    // endregion
    // region测试准确率
    double predictY[testDataset.amount];
    double actualY[testDataset.amount];
    for (int j = 0; j < testDataset.amount; ++j) {
        actualY[j] = testDataset.data[(PARA_NUM) * (j + 1) - 1];
        double x[PARA_NUM];
        for (int a = 1; a < PARA_NUM; ++a) {
            x[a] = trainDataset.data[(PARA_NUM) * j + a - 1];
        }
        x[0] = 1.0;
        predictY[j] = PredictionFunction(PARA_NUM, parameters, x);
    }
    double error = RMSE(testDataset.amount, predictY, actualY);
    printf("***************************************************\nAfter test, testDataset the error(RMSE) is %lf",
           error);
    // endregion
    free(trainDataset.data);
    free(testDataset.data);
    return 0;
}

void FileReaderAndSeparation(char filePath[], double ratio, dataset *train, dataset *test) {
    FILE *datasource = fopen(filePath, "r");
    // 过滤表头
    char s[20];
    for (int i = 0; i < PARA_NUM; ++i) {
        fscanf(datasource, "%s", s);
    }
    // 读取数据
    double data[DATA_NUM * PARA_NUM + 1];
    for (int i = 0; fscanf(datasource, "%lf", &data[i]) != EOF; ++i);
    fclose(datasource);

    // 数据归一化,每一列都需要
    for (int i = 0; i < PARA_NUM; ++i) {
        // 纵向提取出该列
        double feature[DATA_NUM];
        for (int j = 0; j < DATA_NUM; ++j) {
            feature[j] = data[PARA_NUM * j + i];
        }
        FlatData(DATA_NUM, feature);
        for (int j = 0; j < DATA_NUM; ++j) {
            data[PARA_NUM * j + i] = feature[j];
        }

    }

    // 洗牌算法打乱数据 打乱5次 预计sleep2.5s
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < DATA_NUM; ++j) {
            //_sleep(1);
            srand((unsigned) time(NULL));
            // 与第change行交换
            int change = rand() % DATA_NUM;
            for (int k = 0; k < PARA_NUM; ++k) {
                double temp = data[PARA_NUM * j + k];
                data[PARA_NUM * j + k] = data[PARA_NUM * change + k];
                data[PARA_NUM * change + k] = temp;
            }
        }
    }
    // 划分数据集
    train->amount = (int) (ratio * DATA_NUM);
    test->amount = DATA_NUM - train->amount;
    train->data = (double *) malloc(train->amount * PARA_NUM * sizeof(double));
    test->data = (double *) malloc(test->amount * PARA_NUM * sizeof(double));
    int cnt;
    for (cnt = 0; cnt < train->amount * PARA_NUM; ++cnt) {
        train->data[cnt] = data[cnt];
    }
    for (int j = 0, i = cnt - 1; j < test->amount * PARA_NUM; ++i, ++j) {
        test->data[j] = data[i];
    }

}

void FlatData(int dataCnt, double data[]) {
    double max = data[0], min = data[0];
    for (int i = 1; i < dataCnt; ++i) {
        max = data[i] > max ? data[i] : max;
        min = data[i] < min ? data[i] : min;
    }
    for (int i = 0; i < dataCnt; ++i) {
        data[i] /= (max - min);
    }
}

double PredictionFunction(int cnt, const double parameters[], const double x[]) {
    double sum = 0.0;
    for (int i = 0; i < cnt; ++i) {
        sum += parameters[i] * x[i];
    }
    return sum;
}

double LossFunction(int dataCnt, double prediction[], double actuality[]) {
    double sum = 0.0;
    for (int i = 0; i < dataCnt; ++i) {
        sum += pow((prediction[i] - actuality[i]), 2);
    }
    sum = sum / (2 * dataCnt);
    return sum;
}

double
GradientDescent(double learningRate, int paraCnt, double parameters[], dataset trainDataset, const double prediction[],
                const double actuality[]) {
    // 对每个参数进行操作
    for (int i = 0; i < paraCnt; ++i) {
        double sum = 0;
        // 对每行进行操作
        for (int j = 0; j < trainDataset.amount; ++j) {
            sum = sum + (prediction[j] - actuality[j]) * trainDataset.data[paraCnt * j + i];
        }
        parameters[i] = parameters[i] - learningRate * sum / trainDataset.amount;
    }
}

double RMSE(int dataCnt, double prediction[], double actuality[]) {
    double rmse;
    double sum = 0.0;
    for (int i = 0; i < dataCnt; ++i) {
        sum += pow((prediction[i] - actuality[i]), 2);
    }
    rmse = sqrt(sum / dataCnt);
    return rmse;
}