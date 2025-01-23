import http from "k6/http";
import { check } from "k6";

const stage_time = "10s";

const RampingVUs = {
  discardResponseBodies: true, // keep-alive connections

  tags: {
    benchmark_runtime: new Date().toISOString(),
    job_name: 'http-ramping-test',
  },

  scenarios: {
    contacts: {
      executor: "ramping-vus",
      startVUs: 10,
      VU: 1000,
      gracefulStop: "10s",
      stages: [
        { duration: stage_time, target: 3000 },
        { duration: stage_time, target: 5000 },
        { duration: stage_time, target: 7000 },
        { duration: stage_time, target: 10000 },
      ],
    },
  },
};

export const options = {
  ...RampingVUs,

};

export default function () {
  const res = http.get(`http://127.0.0.1:8080/api/orders`);
  check(res, { "status was 200": (r) => r.status == 200 });
}
